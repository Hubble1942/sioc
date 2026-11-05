// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Christian Ewald

#include "TestHelpers/SomeClasses.h"

#include <Sioc/Container.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Sioc {

using namespace TestHelpers;

namespace {

/// Uses A only while it's constructed, keeps B.
class UserAndKeeper
{
public:
    UserAndKeeper(A& a, std::shared_ptr<B> b) : a_(&a), b_(std::move(b)) {}

    A* a_;
    std::shared_ptr<B> b_;
};

class WeakHolder
{
public:
    explicit WeakHolder(std::weak_ptr<Base> base) : base_(std::move(base)) {}

    std::weak_ptr<Base> base_;
};

class ConstUser
{
public:
    explicit ConstUser(const Base& base) : base_(&base) {}

    const Base* base_;
};

}

static_assert(!std::is_convertible_v<Injected<Derived>, Derived>, "an instance is never copied");
static_assert(!std::is_convertible_v<Injected<Derived>, Base>, "an instance is never sliced");
static_assert(!std::is_convertible_v<Injected<Base>, std::shared_ptr<Derived>>, "no downcast");
static_assert(!std::is_convertible_v<Injected<Base>, Derived&>, "no downcast");

TEST(InjectedTest, ConvertsToTheSharedPtrOfABase)
{
    const auto instance = std::make_shared<Derived>();
    const Injected<Derived> sut(instance);

    std::shared_ptr<Base> base = sut;

    EXPECT_EQ(instance, base);
    EXPECT_EQ(instance, sut.Get());
}

TEST(InjectedTest, MovesTheSharedPtrOutOfATemporary)
{
    Injected<A> sut(std::make_shared<A>());

    std::shared_ptr<A> moved = std::move(sut);

    EXPECT_EQ(nullptr, sut.Get());  // NOLINT(bugprone-use-after-move): checks that it was moved out
    EXPECT_EQ(1, moved.use_count());
}

TEST(InjectedTest, ConvertsToAReference)
{
    const auto instance = std::make_shared<Derived>();
    const Injected<Derived> sut(instance);

    Base& base = sut;
    const Middle& middle = sut;

    EXPECT_EQ(instance.get(), &base);
    EXPECT_EQ(instance.get(), &middle);
}

TEST(InjectedTest, AccessesTheInstance)
{
    const auto instance = std::make_shared<IntHolder>(42);
    const Injected<IntHolder> sut(instance);

    EXPECT_TRUE(sut);
    EXPECT_EQ(42, sut->value_);
    EXPECT_EQ(instance.get(), &*sut);
    EXPECT_FALSE(Injected<IntHolder>(nullptr));
}

TEST(InjectedTest, TypePassesWhatTheConstructorAsksFor)
{
    Container sut;

    sut.RegisterType<A>().SingleInstance();
    sut.RegisterType<B>();
    sut.Register(TYPE(UserAndKeeper, INJECT(A), INJECT(B)));
    sut.Register(TYPE(WeakHolder, INJECT(Middle)));
    sut.Register(TYPE(ConstUser, INJECT(Middle)));
    sut.RegisterType<Derived>().As<Middle>().SingleInstance();

    const auto userAndKeeper = sut.Resolve<UserAndKeeper>();
    EXPECT_EQ(sut.Resolve<A>().get(), userAndKeeper->a_);
    EXPECT_EQ(1, userAndKeeper->b_.use_count());

    EXPECT_EQ(sut.Resolve<Middle>(), sut.Resolve<WeakHolder>()->base_.lock());
    EXPECT_EQ(sut.Resolve<Middle>().get(), sut.Resolve<ConstUser>()->base_);
}

TEST(InjectedTest, InjectNamedPassesWhatTheConstructorAsksFor)
{
    Container sut;

    sut.RegisterType<A>().Named<A>("a").SingleInstance();
    sut.RegisterType<B>().Named<B>("b");
    sut.Register(TYPE(UserAndKeeper, INJECT_NAMED(A, "a"), INJECT_NAMED(B, "b")));

    const auto userAndKeeper = sut.Resolve<UserAndKeeper>();

    EXPECT_EQ(sut.ResolveNamed<A>("a").get(), userAndKeeper->a_);
    EXPECT_NE(nullptr, userAndKeeper->b_);
}

TEST(InjectedTest, FactoryReturnsAnInjectedInstance)
{
    Container sut;

    sut.RegisterType<Derived>().Named<Middle>("original").SingleInstance();
    sut.Register(FACTORY(INJECT_NAMED(Middle, "original")));

    EXPECT_EQ(sut.ResolveNamed<Middle>("original"), sut.Resolve<Middle>());
}

TEST(InjectedTest, KeptInjectedInstancesConvertLater)
{
    Container sut;

    sut.RegisterType<A>().SingleInstance();
    sut.RegisterType<B>();
    sut.Register(FACTORY(([a = INJECT(A), b = INJECT(B)]() { return std::make_shared<UserAndKeeper>(a, b); })()));

    const auto userAndKeeper = sut.Resolve<UserAndKeeper>();

    EXPECT_EQ(sut.Resolve<A>().get(), userAndKeeper->a_);
    EXPECT_NE(nullptr, userAndKeeper->b_);
}

}
