// The MIT License(MIT)
//
// Copyright(c) 2014 Christian Ewald
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
