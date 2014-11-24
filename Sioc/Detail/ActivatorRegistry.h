#pragma once

// local
#include "TypeInfo.h"

// STL
#include <memory>
#include <unordered_map>
#include <list>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

// local forwards
class IActivator;

/// <summary>
/// The registry mapping registered types to their activators.
/// </summary>
class ActivatorRegistry : private boost::noncopyable
{
public:
    /// <summary>
    /// Collection of activators.
    /// </summary>
    typedef std::list<std::shared_ptr<const Detail::IActivator>> Activators;

private:
    typedef std::unordered_map<Detail::TypeInfo::IdType, Activators> Registry;

public:
    /// <summary>
    /// Inserts an activator for the specified identifier.
    /// </summary>
    /// <param name="id">The type identifier.</param>
    /// <param name="activator">The activator.</param>
    void Insert(const TypeInfo::IdType& id, const std::shared_ptr<const IActivator>& activator)
    {
        registry_[id].push_back(activator);
    }

    /// <summary>
    /// Gets the activators for a specified type.
    /// </summary>
    /// <param name="id">The type identifier.</param>
    /// <returns>The activators or <c>nullptr</c> if no activator has been found for the specified id.</returns>
    const Activators* GetAllForType(const TypeInfo::IdType& id) const
    {
        auto found = registry_.find(id);

        if (found != registry_.end())
        {
            return &(found->second);
        }

        return nullptr;
    }

private:
    Registry registry_;
};

}
}