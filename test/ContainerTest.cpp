
// framework
#include <gtest/gtest.h>

// sut
#include <Sioc/Container.h>

#include "Mock.h"

namespace Sioc
{

TEST(ContainerTest, SimpleRegisterResolve)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>();

    auto instance = sut.Resolve<DefaultConstructable>();

    ASSERT_NE(nullptr, instance);
}

TEST(ContainerTest, InjectSomeArguments)
{
    Container sut;

    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(42);
    });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(42, instance->arg0_);
}

TEST(ContainerTest, FactoryMethod)
{
    Container sut;

    sut.RegisterFactory<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(4711);
    });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(4711, instance->arg0_);
}

TEST(ContainerTest, MultipleRegistrationToSameTypeResolvesToLast)
{
    Container sut;

    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(42);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(4711);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(31415);
    });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(31415, instance->arg0_);
}

TEST(ContainerTest, ResolveAllGetsAll)
{
    Container sut;

    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(42);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(4711);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return new NonDefaultCtor(31415);
    });

    auto instances = sut.ResolveAll<NonDefaultCtor>();

    ASSERT_EQ(3, instances.size());
    ASSERT_NE(nullptr, instances[0]);
    EXPECT_EQ(42, instances[0]->arg0_);
    ASSERT_NE(nullptr, instances[1]);
    EXPECT_EQ(4711, instances[1]->arg0_);
    ASSERT_NE(nullptr, instances[2]);
    EXPECT_EQ(31415, instances[2]->arg0_);
}

TEST(ContainerTest, MultipleRegistrationsInOneAreIgnored)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>().As<Base>().As<Base>();

    auto bases = sut.ResolveAll<Base>();
    ASSERT_EQ(1, bases.size());
}

TEST(ContainerTest, DerivedAsBase)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    auto base = sut.Resolve<Base>();
    ASSERT_NE(nullptr, base);

    auto derived = std::dynamic_pointer_cast<Derived>(base);
    ASSERT_NE(nullptr, derived);
}

TEST(ContainerTest, DerivedAsMiddleAndBase)
{
    Container sut;

    sut.RegisterType<Derived>().As<Middle>().As<Base>();

    auto base = sut.Resolve<Base>();
    ASSERT_NE(nullptr, base);

    auto middle = std::dynamic_pointer_cast<Middle>(base);
    ASSERT_NE(nullptr, middle);

    auto derived = std::dynamic_pointer_cast<Derived>(base);
    ASSERT_NE(nullptr, derived);
}

TEST(ContainerTest, AsKeepsOriginalRegistration)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    auto derived = sut.Resolve<Derived>();
    ASSERT_NE(nullptr, derived);
}

TEST(ContainerTest, DefaultTransientInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>();

    auto derived1 = sut.Resolve<DefaultConstructable>();

    auto derived2 = sut.Resolve<DefaultConstructable>();
    ASSERT_NE(derived1, derived2);
}

TEST(ContainerTest, SingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().SingleInstance();

    auto derived1 = sut.Resolve<DefaultConstructable>();

    auto derived2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(derived1, derived2);
}

TEST(ContainerTest, WeakSingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().WeakSingleInstance();

    auto derived1 = sut.Resolve<DefaultConstructable>();

    auto derived2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(derived1, derived2);
}

TEST(ContainerTest, SingleInstanceIsSingle)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().SingleInstance();

    DefaultConstructable* derived1Unsafe = 0;
    {
        auto derived1 = sut.Resolve<DefaultConstructable>();
        derived1Unsafe = derived1.get();
    }

    
    auto derived2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(derived1Unsafe, derived2.get());
}

TEST(ContainerTest, WeakSingleInstanceIsWeak)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().WeakSingleInstance();

    DefaultConstructable* derived1Unsafe = 0;
    {
        auto derived1 = sut.Resolve<DefaultConstructable>();
        derived1Unsafe = derived1.get();
    }

    auto derived2 = sut.Resolve<DefaultConstructable>();
    ASSERT_NE(derived1Unsafe, derived2.get());
}

}