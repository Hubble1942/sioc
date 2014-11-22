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
    void registerType()
    {
        registerFactory<T>([](const Container&){ return std::make_shared<T>(); });
    }

    template<typename T>
    void registerType(std::function<T*(const Container&)> delegate)
    {
        registerFactory<T>([delegate](const Container& c){ return std::shared_ptr<T>(delegate(c)); });
    }

    template<typename T>
    void registerFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
    {}

    template<typename T>
    std::shared_ptr<T> resolve() const
    {
        return std::shared_ptr<T>();
    }
};

}