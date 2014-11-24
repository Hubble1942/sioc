#pragma once

// local
#include "IActivator.h"

// STL
#include <memory>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

class SingleInstanceActivatorFacade : public IActivator, private boost::noncopyable
{
public:
    explicit SingleInstanceActivatorFacade(std::shared_ptr<const IActivator> activator)
        : activator_(activator)
    {}

    virtual std::shared_ptr<void> Activate(const Container& container) const
    {
        if (instance_ == nullptr)
        {
            instance_ = activator_->Activate(container);
        }

        return instance_;
    }

private:
    std::shared_ptr<const IActivator> activator_;
    mutable std::shared_ptr<void> instance_;
};

}
}