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
#include "Detail/RegistrationModifier.h"
#include "Detail/ActivatorRegistry.h"
#include "Detail/TypeInfo.h"
#include "Detail/GenericActivator.h"

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
    /// Registers the type.
    /// </summary>
    template<typename T>
    Detail::RegistrationModifier<T> RegisterType()
    {
        return RegisterFactory<T>([](const Container&)
        {
            return std::make_shared<T>();
        });
    }

    /// <summary>
    /// Registers the type.
    /// </summary>
    /// <param name="delegate">The delegate constructing the instance.</param>
    template<typename T>
    Detail::RegistrationModifier<T> RegisterType(std::function<T*(const Container&)> delegate)
    {
        return RegisterFactory<T>([delegate](const Container & c)
        {
            return std::shared_ptr<T>(delegate(c));
        });
    }

    /// <summary>
    /// Registers the factory.
    /// </summary>
    /// <param name="delegate">The delegate constructing the instance.</param>
    template<typename T>
    Detail::RegistrationModifier<T> RegisterFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {
        auto activator = std::make_shared<Detail::GenericActivator>(delegate);
        Detail::RegistrationModifier<T> registrationModifier(registry_, activator);

        registrationModifier.template As<T>();

        return registrationModifier;
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

#define CREATE(statement) [](const Sioc::Container& c) -> decltype(statement) { return statement; }
#define INJECT(type) c.Resolve<type>()

}
