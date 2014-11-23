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
    ASSERT_EQ(TypeInfo::Id<DefaultConstructable>(), TypeInfo::Id<DefaultConstructable>());
    ASSERT_EQ(TypeInfo::Id<NonDefaultCtor>(), TypeInfo::Id<NonDefaultCtor>());
}

TEST(TypeInfoTest, DifferentTypeDifferentInfo)
{
    ASSERT_NE(TypeInfo::Id<DefaultConstructable>(), TypeInfo::Id<NonDefaultCtor>());
    ASSERT_NE(TypeInfo::Id<NonDefaultCtor>(), TypeInfo::Id<DefaultConstructable>());
}

}
}