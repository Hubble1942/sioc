#pragma once

// local
#include "Detail/TypeInfo.h"
#include "Detail/GenericActivator.h"

// STL
#include <memory>
#include <functional>
#include <unordered_map>
#include <list>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{

class Container : private boost::noncopyable
{
private:
    typedef std::list<std::shared_ptr<const Detail::IActivator>> TypeActivators;
    typedef std::unordered_map<Detail::TypeInfo::IdType, TypeActivators> ActivatorRegistry;

public:
    template<typename T>
    void RegisterType()
    {
        RegisterFactory<T>([](const Container&)
        {
            return std::make_shared<T>();
        });
    }

    template<typename T>
    void RegisterType(std::function<T*(const Container&)> delegate)
    {
        RegisterFactory<T>([delegate](const Container & c)
        {
            return std::shared_ptr<T>(delegate(c));
        });
    }

    template<typename T>
    void RegisterFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {
        registry_[Detail::TypeInfo::Id<T>()].push_back(std::make_shared<Detail::GenericActivator<T>>(delegate));
    }

    template<typename T>
    std::shared_ptr<T> Resolve() const
    {
        auto activators = ActivatorsForType(Detail::TypeInfo::Id<T>());

        if (activators != nullptr)
        {
            return std::static_pointer_cast<T>(activators->back()->Activate(*this));
        }

        return std::shared_ptr<T>();
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> ResolveAll() const
    {
        auto activators = ActivatorsForType(Detail::TypeInfo::Id<T>());

        std::vector<std::shared_ptr<T>> instances;
        if (activators != nullptr)
        {
            instances.reserve(activators->size());

            for (auto activator : *activators)
            {
                instances.push_back(std::static_pointer_cast<T>(activator->Activate(*this)));
            }
        }

        return instances;
    }

private:
    const TypeActivators* ActivatorsForType(Detail::TypeInfo::IdType typeId) const
    {
        auto found = registry_.find(typeId);

        if (found != registry_.end())
        {
            return &(found->second);
        }

        return nullptr;
    }

private:
    ActivatorRegistry registry_;
};

}
