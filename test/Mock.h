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

}