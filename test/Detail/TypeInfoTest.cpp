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
#include <Sioc/Detail/TypeInfo.h>

#include <test/Mock.h>

namespace Sioc
{
namespace Detail
{

TEST(TypeInfoTest, SameTypeSameInfo)
{
    EXPECT_EQ(TypeInfo::Id<DefaultConstructable>(""), TypeInfo::Id<DefaultConstructable>(""));
    EXPECT_EQ(TypeInfo::Id<NonDefaultCtor>(""), TypeInfo::Id<NonDefaultCtor>(""));
}

TEST(TypeInfoTest, DifferentTypeDifferentInfo)
{
    EXPECT_NE(TypeInfo::Id<DefaultConstructable>(""), TypeInfo::Id<NonDefaultCtor>(""));
    EXPECT_NE(TypeInfo::Id<NonDefaultCtor>(""), TypeInfo::Id<DefaultConstructable>(""));
}

TEST(TypeInfoTest, SameNameSameInfo)
{
    EXPECT_EQ(TypeInfo::Id<DefaultConstructable>("Foo"), TypeInfo::Id<DefaultConstructable>("Foo"));
    EXPECT_EQ(TypeInfo::Id<NonDefaultCtor>("Bar"), TypeInfo::Id<NonDefaultCtor>("Bar"));
}

TEST(TypeInfoTest, DifferentNameDifferentInfo)
{
    EXPECT_NE(TypeInfo::Id<DefaultConstructable>("Foo"), TypeInfo::Id<DefaultConstructable>("Bar"));
    EXPECT_NE(TypeInfo::Id<NonDefaultCtor>("Bar"), TypeInfo::Id<NonDefaultCtor>("Foo"));
}

}
}