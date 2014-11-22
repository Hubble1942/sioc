
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
    
    sut.registerType<DefaultConstructable>();

    auto instance = sut.resolve<DefaultConstructable>();

    ASSERT_NE(nullptr, instance);
}

TEST(ContainerTest, InjectSomeArguments)
{
    Container sut;

    sut.registerType<NonDefaultCtor>([](const Container&){ return new NonDefaultCtor(42, 4711, 31415); });

    auto instance = sut.resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(42, instance->a_);
    EXPECT_EQ(4711, instance->b_);
    EXPECT_EQ(31415, instance->c_);
}

TEST(ContainerTest, FactoryMethod)
{
    Container sut;

    sut.registerFactory<NonDefaultCtor>([](const Container&){ return std::make_shared<NonDefaultCtor>(4711, 31415, 42); });

    auto instance = sut.resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(4711, instance->a_);
    EXPECT_EQ(31415, instance->b_);
    EXPECT_EQ(42, instance->c_);
}

}