#pragma once

// local
#include "IActivator.h"

// STL
#include <functional>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

/// <summary>
/// Generic activator implementation holding a delegate activating the requested instance.
/// </summary>
class GenericActivator : public IActivator, private boost::noncopyable
{
public:
    explicit GenericActivator(std::function<std::shared_ptr<void>(const Container&)> delegate)
        : delegate_(delegate)
    {}

    /// <summary>
    /// Activates the embedded instance.
    /// </summary>
    /// <param name="container">The ioc container.</param>
    /// <returns>The activated instance.</returns>
    virtual std::shared_ptr<void> Activate(const Container& container) const
    {
        return delegate_(container);
    }

private:
    std::function<std::shared_ptr<void>(const Container&)> delegate_;
};

}
}