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

// STL
#include <cstddef>
#include <functional>
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

    /// <summary>
    /// Hash function for type identifiers.
    /// </summary>
    struct IdHash
    {
        std::size_t operator()(const IdType& id) const
        {
            std::size_t seed = std::hash<std::type_index>()(id.first);
            seed ^= std::hash<std::string>()(id.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };

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