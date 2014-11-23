#pragma once

// local
#include "Detail/TypeInfo.h"
#include "Detail/GenericActivator.h"

// STL
#include <memory>
#include <functional>
#include <unordered_map>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{

class Container : private boost::noncopyable
{
private:
    typedef std::unordered_map<Detail::TypeInfo::IdType, std::shared_ptr<const Detail::IActivator>> ActivatorRegistry;

public:
    template<typename T>
    void RegisterType()
    {
        RegisterFactory<T>([](const Container&){ return std::make_shared<T>(); });
    }

    template<typename T>
    void RegisterType(std::function<T*(const Container&)> delegate)
    {
        RegisterFactory<T>([delegate](const Container& c){ return std::shared_ptr<T>(delegate(c)); });
    }

    template<typename T>
    void RegisterFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {
        registry_[Detail::TypeInfo::Id<T>()] = std::make_shared<Detail::GenericActivator<T>>(delegate);
    }

    template<typename T>
    std::shared_ptr<T> Resolve() const
    {
        auto found = registry_.find(Detail::TypeInfo::Id<T>());

        if (found != registry_.end())
        {
            return std::static_pointer_cast<T>(found->second->Activate(*this));
        }

        return std::shared_ptr<T>();
    }

private:
    ActivatorRegistry registry_;
};

}