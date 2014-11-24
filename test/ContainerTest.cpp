
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

TEST(ContainerTest, DerivedAsBase)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    auto base = sut.Resolve<Base>();
    ASSERT_NE(nullptr, base);

    auto derived = std::dynamic_pointer_cast<Derived>(base);
    ASSERT_NE(nullptr, derived);
}

}