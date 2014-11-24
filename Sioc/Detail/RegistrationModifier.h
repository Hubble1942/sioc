#pragma once

// local
#include "ActivatorRegistry.h"
#include "SingleInstanceActivatorFacade.h"

// STL
#include <type_traits>
#include <cassert>
#include <unordered_set>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

template<typename RegisterType>
class RegistrationModifier : private boost::noncopyable
{
public:
    RegistrationModifier(ActivatorRegistry& registry, std::shared_ptr<IActivator> activator)
        : registry_(registry),
        activator_(activator),
        registeredIds_()
    {}

    RegistrationModifier(RegistrationModifier&& other)
        : registry_(other.registry_),
        activator_(std::move(other.activator_)),
        registeredIds_(std::move(other.registeredIds_))
    {}

    ~RegistrationModifier()
    {
        // the registeredIds_ is empty if we are not at the end of the modification
        for (auto id : registeredIds_)
        {
            registry_.Insert(id, activator_);
        }
    }

    template<typename T>
    RegistrationModifier& As()
    {
        assert(activator_ != nullptr);
        static_assert(std::is_base_of<T, RegisterType>::value, "T must be base of RegisterType");

        registeredIds_.insert(TypeInfo::Id<T>());

        return *this;
    }

    RegistrationModifier& SingleInstance()
    {
        assert(activator_ != nullptr);

        activator_ = std::make_shared<SingleInstanceActivatorFacade>(activator_);

        return *this;
    }

private:
    ActivatorRegistry& registry_;
    std::shared_ptr<const IActivator> activator_;
    std::unordered_set<TypeInfo::IdType> registeredIds_;
};

}
}