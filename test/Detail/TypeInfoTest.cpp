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