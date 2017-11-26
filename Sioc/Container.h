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
#include "Detail/InstanceFactory.h"
#include "Detail/DeduceReturnType.h"
#include "Detail/RegistrationModifier.h"
#include "Detail/ActivatorRegistry.h"
#include "Detail/TypeInfo.h"

// STL
#include <memory>
#include <functional>
#include <vector>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{

/// <summary>
/// The simple inversion of control container.
/// </summary>
class Container : private boost::noncopyable
{
public:

    /// <summary>
    /// Registers a delegate taking a <c>const Container&</c> as argumend and returning an instance.
    /// </summary>
    /// <param name="delegate">The delegate.</param>
    template<typename D, typename T = typename Detail::DeduceReturnType<D>::Type>
    Detail::RegistrationModifier<T> Register(D delegate)
    {
        auto instanceFactory = std::make_shared<Detail::InstanceFactory<T>>(delegate);

        Detail::RegistrationModifier<T> registrationModifier(registry_, instanceFactory);

        registrationModifier.template As<T>();

        return registrationModifier;
    }

    /// <summary>
    /// Registers a (for now default constructible) type.
    /// </summary>
    template<typename T>
    Detail::RegistrationModifier<T> RegisterType()
    {
        return Register([](const Container&)
        {
            return std::make_shared<T>();
        });
    }

    /// <summary>
    /// Registers the type.
    /// </summary>
    /// <param name="delegate">The delegate constructing the instance.</param>
    // TODO: Get rid if this one
    template<typename T>
    Detail::RegistrationModifier<T> RegisterType(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {
        return Register(delegate);
    }

    /// <summary>
    /// Registers an instance.
    /// </summary>
    /// <param name="instance">The instance.</param>
    template<typename T>
    Detail::RegistrationModifier<T> RegisterInstance(const std::shared_ptr<T>& instance)
    {
        return Register([instance](const Container&)
        {
            return instance;
        });
    }

    /// <summary>
    /// Resolves an instance of a specified type.
    /// </summary>
    template<typename T>
    std::shared_ptr<T> Resolve() const
    {
        return ResolveNamed<T>("");
    }

    /// <summary>
    /// Resolves an instances of a specified type for a specified name.
    /// </summary>
    template<typename T>
    std::shared_ptr<T> ResolveNamed(const std::string& name) const
    {
        auto activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>(name));

        if (!activators.empty())
        {
            return std::static_pointer_cast<T>(activators.back()->Activate(*this));
        }

        return std::shared_ptr<T>();
    }

    /// <summary>
    /// Resolves all instances of a specified type.
    /// </summary>
    template<typename T>
    std::vector<std::shared_ptr<T>> ResolveAll() const
    {
        auto activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>(""));

        std::vector<std::shared_ptr<T>> instances;
        instances.reserve(activators.size());

        for (auto activator : activators)
        {
            instances.push_back(std::static_pointer_cast<T>(activator->Activate(*this)));
        }

        return instances;
    }

private:
    Detail::ActivatorRegistry registry_;
};

#define CREATE0(statement) [](const Sioc::Container&) -> decltype(statement) { return statement; }
#define CREATE(statement) [](const Sioc::Container& c) -> decltype(statement) { return statement; }
#define INJECT(type) c.Resolve<type>()
#define INJECT_NAMED(type, name) c.ResolveNamed<type>(name)

#define MAKE(type, ...) [](const Sioc::Container& c) -> std::shared_ptr<type> { return std::make_shared<type>(__VA_ARGS__); }

}
