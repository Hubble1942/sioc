#pragma once

// STL
#include <typeinfo>
#include <typeindex>
#include <utility>
#include <string>

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
    typedef std::pair<std::type_index, std::string> IdType;

private:
    TypeInfo();

public:
    /// <summary>
    /// Returns the identifier of the given type.
    /// </summary>
    template<typename T>
    static IdType Id(const std::string& name)
    {
        return std::make_pair(std::type_index(typeid(T)), name);
    }
};

}
}