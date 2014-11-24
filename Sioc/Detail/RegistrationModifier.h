#pragma once

// local
#include "ActivatorRegistry.h"

// STL
#include <type_traits>

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
        activator_(activator)
    {}

    RegistrationModifier(RegistrationModifier&& other)
        : registry_(other.registry_),
        activator_(std::move(other.activator_))
    {}


    template<typename T>
    RegistrationModifier& As()
    {
        static_assert(std::is_base_of<T, RegisterType>::value, "T must be base of RegisterType");

        registry_.Insert(TypeInfo::Id<T>(), activator_);

        return *this;
    }

    RegistrationModifier& SingleInstance()
    {
        return *this;
    }

private:
    ActivatorRegistry& registry_;
    std::shared_ptr<const IActivator> activator_;
};

}
}