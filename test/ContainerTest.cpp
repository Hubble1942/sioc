
// framework
#include <gtest/gtest.h>

// sut
#include <sioc/Container.h>

#include "Mock.h"

namespace sioc
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

    sut.RegisterType<NonDefaultCtor>([](const Container&){ return new NonDefaultCtor(42); });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(42, instance->arg0_);
}

TEST(ContainerTest, FactoryMethod)
{
    Container sut;

    sut.RegisterFactory<NonDefaultCtor>([](const Container&){ return std::make_shared<NonDefaultCtor>(4711); });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(4711, instance->arg0_);
}

}