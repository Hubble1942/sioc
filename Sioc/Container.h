#pragma once

// local
#include "Detail/ActivatorRegistry.h"
#include "Detail/TypeInfo.h"
#include "Detail/GenericActivator.h"

// STL
#include <memory>
#include <functional>

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
    void RegisterType()
    {
        RegisterFactory<T>([](const Container&)
        {
            return std::make_shared<T>();
        });
    }

    /// <summary>
    /// Registers the type.
    /// </summary>
    /// <param name="delegate">The delegate constructing the instance.</param>
    template<typename T>
    void RegisterType(std::function<T*(const Container&)> delegate)
    {
        RegisterFactory<T>([delegate](const Container & c)
        {
            return std::shared_ptr<T>(delegate(c));
        });
    }

    /// <summary>
    /// Registers the factory.
    /// </summary>
    /// <param name="delegate">The delegate constructing the instance.</param>
    template<typename T>
    void RegisterFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {
        registry_.Insert(Detail::TypeInfo::Id<T>(), std::make_shared<Detail::GenericActivator>(delegate));
    }

    /// <summary>
    /// Resolves an instance of a specified type.
    /// </summary>
    template<typename T>
    std::shared_ptr<T> Resolve() const
    {
        auto activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>());

        if (activators != nullptr)
        {
            return std::static_pointer_cast<T>(activators->back()->Activate(*this));
        }

        return std::shared_ptr<T>();
    }

    /// <summary>
    /// Resolves all instances of a specified type.
    /// </summary>
    template<typename T>
    std::vector<std::shared_ptr<T>> ResolveAll() const
    {
        auto activators = registry_.GetAllForType(Detail::TypeInfo::Id<T>());

        std::vector<std::shared_ptr<T>> instances;
        if (activators != nullptr)
        {
            instances.reserve(activators->size());

            for (auto activator : *activators)
            {
                instances.push_back(std::static_pointer_cast<T>(activator->Activate(*this)));
            }
        }

        return instances;
    }

private:
    Detail::ActivatorRegistry registry_;
};

}
