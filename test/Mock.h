#pragma once

namespace sioc
{

class DefaultConstructable
{
};

class NonDefaultCtor
{
public:
    NonDefaultCtor(int a, int b, int c)
        : a_(a), b_(b), c_(c)
    {}

    int a_;
    int b_;
    int c_;
};

}