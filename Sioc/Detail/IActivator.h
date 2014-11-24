#pragma once

#include <memory>

namespace Sioc
{

// forwards
class Container;

namespace Detail
{

/// <summary>
/// Common interface for all activators.
/// </summary>
class IActivator
{
public:
    /// <summary>
    /// Finalizes an instance of the <see cref="IActivator"/> class.
    /// </summary>
    virtual ~IActivator() {}

    /// <summary>
    /// Activates the embedded instance.
    /// </summary>
    /// <param name="container">The ioc container.</param>
    /// <returns>The activated instance.</returns>
    virtual std::shared_ptr<void> Activate(const Container& container) const = 0;
};

}
}
