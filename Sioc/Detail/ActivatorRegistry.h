#pragma once

// local
#include "TypeInfo.h"

// STL
#include <memory>
#include <unordered_map>
#include <list>

namespace Sioc
{
namespace Detail
{
class IActivator;

class ActivatorRegistry
{
public:
    typedef std::list<std::shared_ptr<const Detail::IActivator>> TypeActivators;

private:
    typedef std::unordered_map<Detail::TypeInfo::IdType, TypeActivators> Registry;

public:
    void Insert(const TypeInfo::IdType& id, const std::shared_ptr<const IActivator>& activator)
    {
        registry_[id].push_back(activator);
    }

    const TypeActivators* GetAllForType(const TypeInfo::IdType& typeId) const
    {
        auto found = registry_.find(typeId);

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