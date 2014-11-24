#pragma once

// local
#include "ActivatorRegistry.h"
#include "SingleInstanceActivatorFacade.h"
#include "WeakSingleInstanceActivatorFacade.h"

// STL
#include <cassert>
#include <unordered_set>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

class Registration : private boost::noncopyable
{
public:
    Registration(ActivatorRegistry& registry, std::shared_ptr<IActivator> activator)
        : registry_(registry),
        activator_(activator),
        registeredIds_()
    {}

    Registration(Registration&& other)
        : registry_(other.registry_),
        activator_(std::move(other.activator_)),
        registeredIds_(std::move(other.registeredIds_))
    {}

    ~Registration()
    {
        // registeredIds_ is empty if we are not at the end of the modification.
        // the content will have been moved away.
        for (auto id : registeredIds_)
        {
            registry_.Insert(id, activator_);
        }
    }

    void As(const TypeInfo::IdType& id)
    {
        assert(activator_ != nullptr);
        
        registeredIds_.insert(id);
    }

    void SingleInstance()
    {
        assert(activator_ != nullptr);

        activator_ = std::make_shared<SingleInstanceActivatorFacade>(activator_);
    }

    void WeakSingleInstance()
    {
        assert(activator_ != nullptr);

        activator_ = std::make_shared<WeakSingleInstanceActivatorFacade>(activator_);
    }

private:
    ActivatorRegistry& registry_;
    std::shared_ptr<const IActivator> activator_;
    std::unordered_set<TypeInfo::IdType> registeredIds_;
};

}
}