// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

namespace Sioc { class Container; }

namespace Sioc { namespace Detail {

enum class LifeCyclePolicy : std::uint8_t
{
    Transient,
    SingleInstance,
    WeakSingleInstance,
};

template<typename T>
class InstanceFactory
{
public:
    explicit InstanceFactory(std::function<std::shared_ptr<T>(const Container&)> delegate)
        : delegate_(std::move(delegate))
    {
    }

    InstanceFactory(const InstanceFactory&) = delete;
    InstanceFactory& operator=(const InstanceFactory&) = delete;

    std::shared_ptr<T> Produce(const Container& container) const
    {
        std::shared_ptr<T> product;

        switch (lifeCyclePolicy_)
        {
            case LifeCyclePolicy::SingleInstance:
                if (singleProduct_ == nullptr)
                {
                    singleProduct_ = delegate_(container);
                }
                product = singleProduct_;
                break;

            case LifeCyclePolicy::WeakSingleInstance:
                product = weakSingleProduct_.lock();
                if (product == nullptr)
                {
                    product = delegate_(container);
                    weakSingleProduct_ = product;
                }
                break;

            default:
                product = delegate_(container);
        }

        return product;
    }

    void SetLifeCyclePolicy(LifeCyclePolicy lifeCyclePolicy) { lifeCyclePolicy_ = lifeCyclePolicy; }

private:
    std::function<std::shared_ptr<T>(const Container&)> delegate_;
    LifeCyclePolicy lifeCyclePolicy_ = LifeCyclePolicy::Transient;
    mutable std::shared_ptr<T> singleProduct_;
    mutable std::weak_ptr<T> weakSingleProduct_;
};

}}
