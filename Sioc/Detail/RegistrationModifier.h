// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include "ActivatorRegistry.h"
#include "GenericActivator.h"
#include "InstanceFactory.h"

#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace Sioc { namespace Detail {

template<typename RegisterType>
class RegistrationModifier
{
private:
    using Activators
        = std::unordered_map<Detail::TypeInfo::IdType, std::shared_ptr<const IActivator>, Detail::TypeInfo::IdHash>;

public:
    RegistrationModifier(ActivatorRegistry& registry, std::shared_ptr<InstanceFactory<RegisterType>> instanceFactory)
        : registry_(registry), instanceFactory_(std::move(instanceFactory))
    {
    }

    RegistrationModifier(RegistrationModifier&& other) noexcept
        : registry_(other.registry_)
        , instanceFactory_(std::move(other.instanceFactory_))
        , activators_(std::move(other.activators_))
    {
    }

    RegistrationModifier(const RegistrationModifier&) = delete;
    RegistrationModifier& operator=(const RegistrationModifier&) = delete;

    ~RegistrationModifier()
    {
        for (const auto& element : activators_)
        {
            registry_.Insert(element.first, element.second);
        }
    }

    template<typename T>
    RegistrationModifier& As()
    {
        return Named<T>("");
    }

    template<typename T>
    RegistrationModifier& Named(const std::string& name)
    {
        static_assert(std::is_base_of_v<T, RegisterType>, "T must be base of RegisterType");

        activators_[TypeInfo::Id<T>(name)] = std::make_shared<GenericActivator<T, RegisterType>>(instanceFactory_);

        return *this;
    }

    RegistrationModifier& SingleInstance()
    {
        instanceFactory_->SetLifeCyclePolicy(LifeCyclePolicy::SingleInstance);

        return *this;
    }

    RegistrationModifier& WeakSingleInstance()
    {
        instanceFactory_->SetLifeCyclePolicy(LifeCyclePolicy::WeakSingleInstance);

        return *this;
    }

private:
    ActivatorRegistry& registry_;
    std::shared_ptr<InstanceFactory<RegisterType>> instanceFactory_;
    Activators activators_;
};

}}
