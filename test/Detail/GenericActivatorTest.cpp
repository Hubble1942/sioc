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
#include <Sioc/Detail/GenericActivator.h>

#include <Sioc/Container.h>
#include <test/Mock.h>

namespace Sioc
{
namespace Detail
{

TEST(GenericActivatorTest, JustActivate)
{
    GenericActivator sut([](const Container&)
    {
        return std::make_shared<DefaultConstructable>();
    });
    Container container;

    auto instance = sut.Activate(container);

    ASSERT_NE(nullptr, instance);
}

TEST(GenericActivatorTest, ActivateNonDefaultCtorable)
{
    GenericActivator sut([](const Container&)
    {
        return std::make_shared<NonDefaultCtor>(42);
    });
    Container container;

    auto instance = sut.Activate(container);

    ASSERT_NE(nullptr, instance);
    auto instanceAgain = std::static_pointer_cast<NonDefaultCtor>(instance);

    ASSERT_NE(nullptr, instanceAgain);
    EXPECT_EQ(42, instanceAgain->arg0_);
}

}
}