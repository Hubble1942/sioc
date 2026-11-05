// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#include "TestHelpers/SomeClasses.h"
#include <gtest/gtest.h>
#include <Sioc/Container.h>

namespace Sioc
{

using namespace TestHelpers;

TEST(NamedTest, RightNameGivesInstance)
{
    Container sut;

    sut.RegisterType<A>().Named<A>("Foo");

    auto resolved = sut.ResolveNamed<A>("Foo");

    ASSERT_NE(nullptr, resolved);
}

TEST(NamedTest, WrongNameGivesNoInstance)
{
    Container sut;

    sut.RegisterType<A>().Named<A>("Foo");

    auto resolved = sut.ResolveNamed<A>("Bar");

    ASSERT_EQ(nullptr, resolved);
}

TEST(NamedTest, StillAccessibleWithoutName)
{
    Container sut;

    sut.RegisterType<A>().Named<A>("Foo");

    auto resolved = sut.Resolve<A>();

    ASSERT_NE(nullptr, resolved);
}

}
