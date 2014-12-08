// The MIT License(MIT)
//
// Copyright(c) 2014 Christian Ewald
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#pragma once

// local
#include "ActivatorRegistry.h"
#include "InstanceFactory.h"
#include "GenericActivator.h"

// STL
#include <type_traits>
#include <unordered_map>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

template<typename RegisterType>
class RegistrationModifier : private boost::noncopyable
{
private:
    typedef std::unordered_map<Detail::TypeInfo::IdType, std::shared_ptr<const IActivator>, boost::hash<Detail::TypeInfo::IdType>> Activators;

public:
    RegistrationModifier(ActivatorRegistry& registry, std::shared_ptr<InstanceFactory<RegisterType>> instanceFactory)
        : registry_(registry),
          instanceFactory_(std::move(instanceFactory))
    {}

    RegistrationModifier(RegistrationModifier&& other)
        : registry_(other.registry_),
          instanceFactory_(std::move(other.instanceFactory_)),
          activators_(std::move(other.activators_))
    {}

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
        static_assert(std::is_base_of<T, RegisterType>::value, "T must be base of RegisterType");

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

}
}