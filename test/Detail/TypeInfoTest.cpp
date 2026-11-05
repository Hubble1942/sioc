// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

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
