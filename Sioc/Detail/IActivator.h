#pragma once

#include <memory>

namespace Sioc
{

// forwards
class Container;

namespace Detail
{

class IActivator
{
public:
    virtual ~IActivator() {}

    virtual std::shared_ptr<void> Activate(const Container&) const = 0;

    template<typename T>
    std::shared_ptr<T> ActivateTyped(const Container& c) const
    {
        return std::static_pointer_cast<T>(Activate(c));
    }
};

}
}