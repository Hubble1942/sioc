#pragma once

// local
#include "ActivatorRegistry.h"

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

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
        registry_.Insert(TypeInfo::Id<T>(), activator_);

        return *this;
    }

private:
    ActivatorRegistry& registry_;
    std::shared_ptr<const IActivator> activator_;
};

}
}