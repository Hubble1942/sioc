#pragma once

#include <boost/type_index.hpp>

namespace Sioc
{
namespace Detail
{

class TypeInfo
{
public:
    typedef boost::typeindex::type_index IdType;

private:
    TypeInfo();

public:
    template<typename T>
    static IdType Id()
    {
        return boost::typeindex::type_id<T>();
    }
};

}
}