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
    virtual ~IActivator(){}

    virtual std::shared_ptr<void> Activate(const Container&) const = 0;
};

}
}