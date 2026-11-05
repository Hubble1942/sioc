// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <cstddef>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <utility>
#include <string>

namespace Sioc { namespace Detail {

/// Identifies a registration by its type and name.
class TypeInfo
{
public:
    using IdType = std::pair<std::type_index, std::string>;

    struct IdHash
    {
        std::size_t operator()(const IdType& id) const
        {
            std::size_t seed = std::hash<std::type_index>()(id.first);
            seed ^= std::hash<std::string>()(id.second) + 0x9e3779b9 + (seed << 6U) + (seed >> 2U);
            return seed;
        }
    };

    TypeInfo() = delete;

    /// An unnamed registration has the empty name.
    template<typename T>
    static IdType Id(const std::string& name)
    {
        return std::make_pair(std::type_index(typeid(T)), name);
    }
};

} }
