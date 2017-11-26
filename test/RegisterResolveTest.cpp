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

TEST(RegisterResolveTest, SimpleRegisterResolve)
{
    Container sut;

    sut.RegisterType<A>();
    sut.RegisterType<B>();
    sut.RegisterType<C>();
    sut.Register(SIOC_CREATE(Aggregate, SIOC_INJECT(A), SIOC_INJECT(B), SIOC_INJECT(C)));

    auto aggregate = sut.Resolve<Aggregate>();

    ASSERT_NE(nullptr, aggregate);
    EXPECT_NE(nullptr, aggregate->a_);
    EXPECT_NE(nullptr, aggregate->b_);
    EXPECT_NE(nullptr, aggregate->c_);
}

}
