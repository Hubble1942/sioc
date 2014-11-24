#pragma once

// local
#include "Registration.h"

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
        : registration_(registry, activator)
    {}

    RegistrationModifier(RegistrationModifier&& other)
        : registration_(std::move(other.registration_))
    {}

    template<typename T>
    RegistrationModifier& As()
    {
        static_assert(std::is_base_of<T, RegisterType>::value, "T must be base of RegisterType");

        registration_.As(TypeInfo::Id<T>());

        return *this;
    }

    RegistrationModifier& SingleInstance()
    {
        registration_.SingleInstance();

        return *this;
    }

    RegistrationModifier& WeakSingleInstance()
    {
        registration_.WeakSingleInstance();

        return *this;
    }

private:
    Registration registration_;
};

}
}