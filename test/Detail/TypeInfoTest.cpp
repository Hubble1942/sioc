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

#include "../TestHelpers/SomeClasses.h"
#include <gtest/gtest.h>
#include <Sioc/Detail/TypeInfo.h>

namespace Sioc { namespace Detail {

using namespace TestHelpers;

TEST(TypeInfoTest, SameTypeSameInfo)
{
    EXPECT_EQ(TypeInfo::Id<A>(""), TypeInfo::Id<A>(""));
    EXPECT_EQ(TypeInfo::Id<Aggregate>(""), TypeInfo::Id<Aggregate>(""));
}

TEST(TypeInfoTest, DifferentTypeDifferentInfo)
{
    EXPECT_NE(TypeInfo::Id<A>(""), TypeInfo::Id<Aggregate>(""));
    EXPECT_NE(TypeInfo::Id<Aggregate>(""), TypeInfo::Id<A>(""));
}

TEST(TypeInfoTest, SameNameSameInfo)
{
    EXPECT_EQ(TypeInfo::Id<A>("Foo"), TypeInfo::Id<A>("Foo"));
    EXPECT_EQ(TypeInfo::Id<Aggregate>("Bar"), TypeInfo::Id<Aggregate>("Bar"));
}

TEST(TypeInfoTest, DifferentNameDifferentInfo)
{
    EXPECT_NE(TypeInfo::Id<A>("Foo"), TypeInfo::Id<A>("Bar"));
    EXPECT_NE(TypeInfo::Id<Aggregate>("Bar"), TypeInfo::Id<Aggregate>("Foo"));
}

} }
