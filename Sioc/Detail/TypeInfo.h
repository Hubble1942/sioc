// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace Sioc { namespace Detail { namespace TypeInfo {

/// Identifies a registration by its type and name.
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

/// An unnamed registration has the empty name.
template<typename T>
IdType Id(const std::string& name)
{
    return std::make_pair(std::type_index(typeid(T)), name);
}

}}}
