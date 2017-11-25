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
        return std::make_shared<NonDefaultCtor>(42);
    });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(42, instance->arg0_);
}

TEST(ContainerTest, InjectSomeArgumentsMacro)
{
    Container sut;

    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(42);
    });

    auto instance = sut.Resolve<NonDefaultCtor>();

    ASSERT_NE(nullptr, instance);
    EXPECT_EQ(42, instance->arg0_);
}

TEST(ContainerTest, MultipleRegistrationToSameTypeResolvesToLast)
{
    Container sut;

    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(42);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(4711);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(31415);
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
        return std::make_shared<NonDefaultCtor>(42);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(4711);
    });
    sut.RegisterType<NonDefaultCtor>([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(31415);
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

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_NE(instance1, instance2);
}

TEST(ContainerTest, SingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().SingleInstance();

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(instance1, instance2);
}

TEST(ContainerTest, WeakSingleInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().WeakSingleInstance();

    auto instance1 = sut.Resolve<DefaultConstructable>();

    auto instance2 = sut.Resolve<DefaultConstructable>();
    ASSERT_EQ(instance1, instance2);
}

TEST(ContainerTest, SingleInstanceIsSingle)
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

TEST(ContainerTest, WeakSingleInstanceIsWeak)
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

TEST(ContainerTest, NamedRightNameGivesInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.ResolveNamed<DefaultConstructable>("Foo");

    ASSERT_NE(nullptr, instance);
}

TEST(ContainerTest, NamedWrongNameNoInstance)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.ResolveNamed<DefaultConstructable>("Bar");

    ASSERT_EQ(nullptr, instance);
}

TEST(ContainerTest, NamedIsStillAccessibleWithoutName)
{
    Container sut;

    sut.RegisterType<DefaultConstructable>().Named<DefaultConstructable>("Foo");

    auto instance = sut.Resolve<DefaultConstructable>();

    ASSERT_NE(nullptr, instance);
}

TEST(ContainerTest, CtorInjectRaw)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();
    sut.RegisterType<BaseHolder>([](const Container & c)
    {
        return std::make_shared<BaseHolder>(c.Resolve<Base>());
    });

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(ContainerTest, CtorInjectWithCreateMacro)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();
    sut.RegisterType<BaseHolder>(CREATE(std::make_shared<BaseHolder>(c.Resolve<Base>())));

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(ContainerTest, CtorInjectWithInjectMacro)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();
    sut.RegisterType<BaseHolder>([](const Container & c)
    {
        return std::make_shared<BaseHolder>(INJECT(Base));
    });

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(ContainerTest, CtorInjectWithMacro)
{
    Container sut;

    sut.RegisterType<Derived>().As<Base>();
    sut.RegisterType<BaseHolder>(CREATE(std::make_shared<BaseHolder>(INJECT(Base))));

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(ContainerTest, MultipleInheritance)
{
    Container sut;

    sut.RegisterType<Multiple>().As<Base1>().As<Base2>();

    EXPECT_EQ(1, sut.Resolve<Base1>()->GetBase1Value());
    EXPECT_EQ(2, sut.Resolve<Base2>()->GetBase2Value());
}

TEST(ContainerTest, RegisterInstance)
{
    Container sut;
    auto instance = std::make_shared<DefaultConstructable>();

    sut.RegisterInstance(instance);

    auto resolved = sut.Resolve<DefaultConstructable>();

    ASSERT_EQ(instance, resolved);
}

TEST(ContainerTest, MakeMakroSingleInject)
{
    Container sut;

    sut.RegisterType<Base>();
    sut.RegisterType<BaseHolder>(MAKE(BaseHolder, INJECT(Base)));

    auto instance = sut.Resolve<BaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base_);
}

TEST(ContainerTest, MakeMakroDoubleInject)
{
    Container sut;

    sut.RegisterType<Base>();
    sut.RegisterType<Derived>();
    sut.RegisterType<DoubleBaseHolder>(MAKE(DoubleBaseHolder, INJECT(Base), INJECT(Derived)));

    auto instance = sut.Resolve<DoubleBaseHolder>();

    ASSERT_NE(nullptr, instance);
    EXPECT_NE(nullptr, instance->base1_);
    EXPECT_NE(nullptr, instance->base2_);
}


}