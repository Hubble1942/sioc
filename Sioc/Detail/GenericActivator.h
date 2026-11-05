// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include "IActivator.h"

#include <memory>
#include <type_traits>
#include <utility>

namespace Sioc { namespace Detail {

template<typename TargetType, typename SourceType>
class GenericActivator final : public IActivator
{
public:
    explicit GenericActivator(std::shared_ptr<const InstanceFactory<SourceType>> instanceFactory)
        : instanceFactory_(std::move(instanceFactory))
    {
        static_assert(std::is_base_of_v<TargetType, SourceType>, "TargetType must be base of SourceType");
    }

    GenericActivator(const GenericActivator&) = delete;
    GenericActivator& operator=(const GenericActivator&) = delete;

    std::shared_ptr<void> Activate(const Container& container) const override
    {
        return std::static_pointer_cast<TargetType>(instanceFactory_->Produce(container));
    }

private:
    std::shared_ptr<const InstanceFactory<SourceType>> instanceFactory_;
};

}}
