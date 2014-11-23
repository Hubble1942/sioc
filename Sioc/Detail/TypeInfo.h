#pragma once

// STL
#include <typeinfo>
#include <typeindex>

namespace Sioc
{
namespace Detail
{

class TypeInfo
{
public:
    typedef std::type_index IdType;

private:
    TypeInfo();

public:
    template<typename T>
    static IdType Id()
    {
        return std::type_index(typeid(T));
    }
};

}
}