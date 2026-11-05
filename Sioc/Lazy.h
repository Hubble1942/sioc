// SPDX-License-Identifier: MIT
// Copyright (c) 2018 Christian Ewald

#pragma once

#include <functional>
#include <memory>
#include <utility>

namespace Sioc
{

/// A service that is resolved on the first access.
template<class T>
class Lazy
{
public:
    using Activator = std::function<std::shared_ptr<T>()>;

    explicit Lazy(Activator activator)
        : activator_(std::move(activator))
    {}

    /// Returns the service, resolving it on the first call.
    const std::shared_ptr<T>& Get() const
    {
        Activate();
        return service_;
    }

    void Activate() const
    {
        if (!service_)
        {
            service_ = activator_();
        }
    }

    bool IsActivated() const
    {
        return static_cast<bool>(service_);
    }

private:
    Activator activator_;
    mutable std::shared_ptr<T> service_;
};

}

#define INJECT_LAZY(type) Sioc::Lazy<type>{ [&c]() { return c.Resolve<type>(); } }
