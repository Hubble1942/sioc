// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

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
