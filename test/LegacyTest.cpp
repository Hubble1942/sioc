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

#include "Mock.h"
#include <gtest/gtest.h>
#include <Sioc/Container.h>

namespace Sioc
{

TEST(LegacyTest, MultipleRegistrationsInOneAreIgnored)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>().As<Base>().As<Base>();

    auto bases = sut.ResolveAll<Base>();
    ASSERT_EQ(1, bases.size());
}

TEST(LegacyTest, DerivedAsBase)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    auto base = sut.Resolve<Base>();
    ASSERT_NE(nullptr, base);

    auto derived = std::dynamic_pointer_cast<Derived>(base);
    ASSERT_NE(nullptr, derived);
}

TEST(LegacyTest, DerivedAsMiddleAndBase)
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

TEST(LegacyTest, AsKeepsOriginalRegistration)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();

    auto derived = sut.Resolve<Derived>();
    ASSERT_NE(nullptr, derived);
}

TEST(LegacyTest, DefaultTransientInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>();

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_NE(instance1, instance2);
}

TEST(LegacyTest, SingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().SingleInstance();

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(instance1, instance2);
}

TEST(LegacyTest, WeakSingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().WeakSingleInstance();

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(instance1, instance2);
}

TEST(LegacyTest, SingleInstanceIsSingle)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().SingleInstance();

    DefaultConstructable* instance1Unsafe = 0;
    {
        auto instance1 = sut.Resolve<DefaultConstructable>();
        instance1Unsafe = instance1.get();
    }


    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(instance1Unsafe, instance2.get());
}

TEST(LegacyTest, WeakSingleInstanceIsWeak)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().WeakSingleInstance();

    DefaultConstructable* instance1Unsafe = 0;
    {
        auto instance1 = sut.Resolve<DefaultConstructable>();
        instance1Unsafe = instance1.get();
    }

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_NE(instance1Unsafe, instance2.get());
}

TEST(LegacyTest, NamedRightNameGivesInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.ResolveNamed<DefaultConstructable>("Foo");

    ASSERT_NE(nullptr, instance);
}

TEST(LegacyTest, NamedWrongNameNoInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.ResolveNamed<DefaultConstructable>("Bar");

    ASSERT_EQ(nullptr, instance);
}

TEST(LegacyTest, NamedIsStillAccessibleWithoutName)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.Resolve<DefaultConstructable>();

    ASSERT_NE(nullptr, instance);
}

TEST(LegacyTest, CtorInjectRaw)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();
    sut.RegisterFactory<BaseHolder>([](const Container & c)
    {
        return std::make_shared<BaseHolder>(c.Resolve<Base>());
    });

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(LegacyTest, MultipleInheritance)
{
    Container sut;

    sut.RegisterType<Multiple>().As<Base1>().As<Base2>();

    EXPECT_EQ(1, sut.Resolve<Base1>()->GetBase1Value());
    EXPECT_EQ(2, sut.Resolve<Base2>()->GetBase2Value());
}

TEST(LegacyTest, RegisterInstance)
{
    Container sut;
    auto instance = std::make_shared<DefaultConstructable>();

    sut.RegisterInstance(instance);

    auto resolved = sut.Resolve<DefaultConstructable>();

    ASSERT_EQ(instance, resolved);
}

}
