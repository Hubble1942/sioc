#pragma once

// STL
#include <typeinfo>
#include <typeindex>

namespace Sioc
{
namespace Detail
{

/// <summary>
/// Static wrapper/helper class providing access to type identifiers.
/// </summary>
class TypeInfo
{
public:
    /// <summary>
    /// The type-identifier type.
    /// </summary>
    typedef std::type_index IdType;

private:
    TypeInfo();

public:
    /// <summary>
    /// Returns the identifier of the given type.
    /// </summary>
    template<typename T>
    static IdType Id()
    {
        return std::type_index(typeid(T));
    }
};

}
}