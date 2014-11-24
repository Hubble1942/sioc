#pragma once

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

}