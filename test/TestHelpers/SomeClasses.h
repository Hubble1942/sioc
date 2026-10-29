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
#pragma once

#include <memory>

namespace Sioc { namespace TestHelpers {

class A {};

class B {};

class C {};

class Aggregate
{
public:
    Aggregate(const std::shared_ptr<A>& a, const std::shared_ptr<B>& b, const std::shared_ptr<C>& c)
        : a_(a),
          b_(b),
          c_(c)
    {}

    std::shared_ptr<A> a_;
    std::shared_ptr<B> b_;
    std::shared_ptr<C> c_;
};

class IntHolder
{
public:
    explicit IntHolder(int value)
        : value_(value)
    {}

    int value_;
};

class Base
{
public:
    virtual ~Base() {}
};

class Middle : public Base
{};

class Derived : public Middle
{};

class BaseHolder
{
public:
    explicit BaseHolder(const std::shared_ptr<Base>& base)
        : base_(base)
    {}

    std::shared_ptr<Base> base_;
};

} }
