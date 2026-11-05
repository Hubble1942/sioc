// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include "Detail/ActivatorRegistry.h"
#include "Detail/DeduceReturnType.h"
#include "Detail/InstanceFactory.h"
#include "Detail/IsCompleteType.h"
#include "Detail/RegistrationModifier.h"
#include "Detail/TypeInfo.h"
#include "Injected.h"
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace Sioc
{

    /// The simple inversion of control container.
    class Container
    {
    public:
        Container() = default;
        Container(const Container&) = delete;
        Container& operator=(const Container&) = delete;

        /// Registers a delegate that takes the `const Container&` and returns a `std::shared_ptr` to the
        /// instance.
        template<typename D, typename T = typename Detail::DeduceReturnType<D>::Type>
        Detail::RegistrationModifier<T> Register(D delegate)
        {
            const auto instanceFactory = std::make_shared<Detail::InstanceFactory<T>>(std::move(delegate));

            Detail::RegistrationModifier<T> registrationModifier(registry_, instanceFactory);

            registrationModifier.template As<T>();

            return registrationModifier;
        }

        /// Registers a default constructible type.
        template<typename T>
        Detail::RegistrationModifier<T> RegisterType()
        {
            static_assert(std::is_default_constructible_v<T>, "T must be default constructible");

            return Register([](const Container&)
                {
                    return std::make_shared<T>();
                });
        }

        /// Registers an existing instance, which every resolve returns.
        template<typename T>
        Detail::RegistrationModifier<T> RegisterInstance(std::shared_ptr<T> instance)
        {
            return Register([instance = std::move(instance)](const Container&)
                {
                    return instance;
                });
        }

        /// Returns an empty `std::shared_ptr` if `T` isn't registered; of several registrations, the last one
        /// wins.
        template<typename T>
        std::shared_ptr<T> Resolve() const
        {
            static_assert(Detail::IsCompleteType<T>(), "Resolved types must be complete");

            return ResolveNamed<T>("");
        }

        /// Returns an empty `std::shared_ptr` if `T` isn't registered with `name`; of several registrations,
        /// the last one wins.
        template<typename T>
        std::shared_ptr<T> ResolveNamed(const std::string& name) const
        {
            static_assert(Detail::IsCompleteType<T>(), "Resolved types must be complete");

            const auto& activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>(name));

            if (!activators.empty())
            {
                return std::static_pointer_cast<T>(activators.back()->Activate(*this));
            }

            return std::shared_ptr<T>();
        }

        /// Resolves every unnamed registration of `T`, in the order of registration.
        template<typename T>
        std::vector<std::shared_ptr<T>> ResolveAll() const
        {
            static_assert(Detail::IsCompleteType<T>(), "Resolved types must be complete");

            const auto& activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>(""));

            std::vector<std::shared_ptr<T>> instances;
            instances.reserve(activators.size());

            for (const auto& activator : activators)
            {
                instances.push_back(std::static_pointer_cast<T>(activator->Activate(*this)));
            }

            return instances;
        }

    private:
        Detail::ActivatorRegistry registry_;
    };

#define TYPE(type, ...) [=](const Sioc::Container& c) -> std::shared_ptr<type> { (void)c; return std::make_shared<type>(__VA_ARGS__); }
#define FACTORY(statement) [=](const Sioc::Container& c) { (void)c; return statement; }
#define INJECT(type) Sioc::Injected<type>(c.Resolve<type>())
#define INJECT_FACTORY(type) [&c]() { return c.Resolve<type>(); }
#define INJECT_NAMED(type, name) Sioc::Injected<type>(c.ResolveNamed<type>(name))
#define INJECT_ALL(type) c.ResolveAll<type>()

}
