// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#include "TestHelpers/SomeClasses.h"
#include <gtest/gtest.h>
#include <Sioc/Container.h>

namespace Sioc
{

using namespace TestHelpers;

TEST(LifetimeTest, UnmodifiedRegistrationIsTransient)
{
    Container sut;

    sut.RegisterType<A>();

    auto resolved1 = sut.Resolve<A>();
    auto resolved2 = sut.Resolve<A>();

    EXPECT_NE(resolved1, resolved2);
}

TEST(LifetimeTest, SingleInstanceResolvesAlwaysTheSameInstance)
{
    Container sut;

    sut.RegisterType<A>().SingleInstance();

    void* address = nullptr;

    {
        auto resolved1 = sut.Resolve<A>();
        auto resolved2 = sut.Resolve<A>();

        EXPECT_EQ(resolved1, resolved2);

        address = resolved1.get();
    }

    {
        auto resolved3 = sut.Resolve<A>();

        EXPECT_EQ(address, resolved3.get());
    }
}

TEST(LifetimeTest, WeakSingleInstanceResolvesTheSameInstanceWhileItIsExternallyHeld)
{
    Container sut;

    sut.RegisterType<A>().WeakSingleInstance();

    void* address = nullptr;

    {
        auto resolved1 = sut.Resolve<A>();
        auto resolved2 = sut.Resolve<A>();

        EXPECT_EQ(resolved1, resolved2);

        address = resolved1.get();
    }

    {
        auto resolved3 = sut.Resolve<A>();

        EXPECT_NE(address, resolved3.get());
    }
}

}
