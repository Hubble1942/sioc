// framework
#include <gtest/gtest.h>

// sut
#include <Sioc/Detail/GenericActivator.h>

#include <Sioc/Container.h>
#include <test/Mock.h>

namespace Sioc
{
namespace Detail
{

TEST(GenericActivatorTest, JustActivate)
{
    GenericActivator<DefaultConstructable> sut([](const Container&){ return std::make_shared<DefaultConstructable>(); });
    Container container;

    auto instance = sut.Activate(container);

    ASSERT_NE(nullptr, instance);
}

TEST(GenericActivatorTest, ActivateNonDefaultCtorable)
{
    GenericActivator<NonDefaultCtor> sut([](const Container&){ return std::make_shared<NonDefaultCtor>(42); });
    Container container;

    auto instance = sut.Activate(container);

    ASSERT_NE(nullptr, instance);
    auto instanceAgain = std::static_pointer_cast<NonDefaultCtor>(instance);

    ASSERT_NE(nullptr, instanceAgain);
    EXPECT_EQ(42, instanceAgain->arg0_);
}

}
}