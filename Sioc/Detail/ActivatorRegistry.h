// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include "TypeInfo.h"

#include <list>
#include <memory>
#include <unordered_map>
#include <utility>

namespace Sioc { namespace Detail {

class IActivator;

/// Maps the identifier of each registration to its activators.
class ActivatorRegistry
{
public:
    using Activators = std::list<std::shared_ptr<const Detail::IActivator>>;

private:
    using Registry = std::unordered_map<Detail::TypeInfo::IdType, Activators, Detail::TypeInfo::IdHash>;

public:
    ActivatorRegistry() = default;
    ActivatorRegistry(const ActivatorRegistry&) = delete;
    ActivatorRegistry& operator=(const ActivatorRegistry&) = delete;

    void Insert(const TypeInfo::IdType& id, std::shared_ptr<const IActivator> activator)
    {
        registry_[id].push_back(std::move(activator));
    }

    /// Returns an empty list for an identifier nothing is registered for.
    const Activators& GetAllForType(const TypeInfo::IdType& id) const
    {
        const auto found = registry_.find(id);

        if (found != registry_.end())
        {
            return found->second;
        }

        return empty_;
    }

private:
    Registry registry_;
    Activators empty_;
};

} }
