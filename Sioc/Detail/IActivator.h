// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <memory>

namespace Sioc { class Container; }

namespace Sioc { namespace Detail {

/// Produces the instance of a registration as one of the types it's resolved as.
class IActivator
{
public:
    virtual ~IActivator() = default;

    /// Returns the instance as `std::shared_ptr<void>`, which the container casts back to the resolved type.
    virtual std::shared_ptr<void> Activate(const Container& container) const = 0;
};

}}
