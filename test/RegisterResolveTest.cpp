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

TEST(RegisterResolveTest, SimpleRegisterResolveOfDefaultConstructibleType)
{
    Container sut;

    sut.RegisterType<A>();

    auto resolved = sut.Resolve<A>();

    ASSERT_NE(nullptr, resolved);
}

TEST(RegisterResolveTest, AggregateType)
{
    Container sut;

    sut.RegisterType<A>();
    sut.RegisterType<B>();
    sut.RegisterType<C>();
    sut.Register(TYPE(Aggregate, INJECT(A), INJECT(B), INJECT(C)));

    auto resolved = sut.Resolve<Aggregate>();

    ASSERT_NE(nullptr, resolved);
    EXPECT_NE(nullptr, resolved->a_);
    EXPECT_NE(nullptr, resolved->b_);
    EXPECT_NE(nullptr, resolved->c_);
}

TEST(RegisterResolveTest, InjectIndependentOfTheContainer)
{
    Container sut;

    sut.Register(TYPE(Aggregate, std::make_shared<A>(), std::make_shared<B>(), std::make_shared<C>()));

    auto resolved = sut.Resolve<Aggregate>();

    ASSERT_NE(nullptr, resolved);
}

TEST(RegisterResolveTest, MultipleRegistrationToSameTypeResolvesToLast)
{
    Container sut;

    sut.Register(TYPE(IntHolder, 42));
    sut.Register(TYPE(IntHolder, 4711));
    sut.Register(TYPE(IntHolder, 31415));

    auto resolved = sut.Resolve<IntHolder>();

    ASSERT_NE(nullptr, resolved);
    EXPECT_EQ(31415, resolved->value_);
}

TEST(RegisterResolveTest, ResolveAllGetsAll)
{
    Container sut;

    sut.Register(TYPE(IntHolder, 42));
    sut.Register(TYPE(IntHolder, 4711));
    sut.Register(TYPE(IntHolder, 31415));

    auto all = sut.ResolveAll<IntHolder>();

    ASSERT_EQ(3U, all.size());
    EXPECT_EQ(42, all[0]->value_);
    EXPECT_EQ(4711, all[1]->value_);
    EXPECT_EQ(31415, all[2]->value_);
}

TEST(RegisterResolveTest, RegisterInstance)
{
    Container sut;
    auto instance = std::make_shared<A>();

    sut.RegisterInstance(instance);

    auto resolved = sut.Resolve<A>();

    ASSERT_EQ(instance, resolved);
}

TEST(RegisterResolveTest, FactoryStatementReturningReference)
{
    Container sut;
    auto instance = std::make_shared<A>();
    const auto& reference = instance;

    sut.Register(FACTORY(reference));

    auto resolved = sut.Resolve<A>();

    ASSERT_EQ(instance, resolved);
}

}
