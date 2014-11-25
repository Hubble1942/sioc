#pragma once

#include <memory>

namespace Sioc
{

class DefaultConstructable
{
};

class NonDefaultCtor
{
public:
    explicit NonDefaultCtor(int arg0)
        : arg0_(arg0)
    {}

    int arg0_;
};

class Base
{
public:
    virtual ~Base() {}
};

class Middle : public Base
{
};

class Derived : public Middle
{
};

class BaseHolder
{
public:
    explicit BaseHolder(std::shared_ptr<Base> base)
        : base_(base)
    {}

    std::shared_ptr<Base> base_;
};

}