// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#include "TestHelpers/SomeClasses.h"
#include <gtest/gtest.h>
#include <Sioc/Container.h>

namespace Sioc
{

using namespace TestHelpers;

TEST(AsTypeTest, InheritedTypesArentImplicitlyRegistered)
{
    Container sut;

    sut.RegisterType<Derived>();

    EXPECT_NE(nullptr, sut.Resolve<Derived>());
    EXPECT_EQ(nullptr, sut.Resolve<Middle>());
    EXPECT_EQ(nullptr, sut.Resolve<Base>());
}

TEST(AsTypeTest, ExplicitRegisterInheritedTypes)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    EXPECT_NE(nullptr, sut.Resolve<Derived>());
    EXPECT_EQ(nullptr, sut.Resolve<Middle>());
    EXPECT_NE(nullptr, sut.Resolve<Base>());
}

TEST(AsTypeTest, ExplicitRegisterAllInheritedTypes)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>().As<Middle>();

    EXPECT_NE(nullptr, sut.Resolve<Derived>());
    EXPECT_NE(nullptr, sut.Resolve<Middle>());
    EXPECT_NE(nullptr, sut.Resolve<Base>());
}

TEST(AsTypeTest, TheOriginallyRegisteredTypeIsResolved)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    EXPECT_NE(nullptr, std::dynamic_pointer_cast<Middle>(sut.Resolve<Base>()));
    EXPECT_NE(nullptr, std::dynamic_pointer_cast<Derived>(sut.Resolve<Base>()));
}

TEST(AsTypeTest, AsDoesNotSumUp)
{
    Container sut;

    sut.RegisterType<Base>().As<Base>().As<Base>().As<Base>().As<Base>();

    EXPECT_EQ(1U, sut.ResolveAll<Base>().size());
}

}
