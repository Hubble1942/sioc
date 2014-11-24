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

class WeakSingleInstanceActivatorFacade : public IActivator, private boost::noncopyable
{
public:
    explicit WeakSingleInstanceActivatorFacade(std::shared_ptr<const IActivator> activator)
        : activator_(activator)
    {}

    virtual std::shared_ptr<void> Activate(const Container& container) const
    {
        auto instance = weakInstance_.lock();
        if (instance == nullptr)
        {
            instance = activator_->Activate(container);
            weakInstance_ = instance;
        }

        return instance;
    }

private:
    std::shared_ptr<const IActivator> activator_;
    mutable std::weak_ptr<void> weakInstance_;
};

}
}