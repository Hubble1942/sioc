#pragma once

// STL
#include <memory>
#include <functional>

// boost
#include <boost/noncopyable.hpp>

namespace sioc
{

class Container : private boost::noncopyable
{
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
    {}

    template<typename T>
    std::shared_ptr<T> Resolve() const
    {
        return std::shared_ptr<T>();
    }
};

}