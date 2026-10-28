// The MIT License(MIT)
//
// Copyright(c) 2014 Christian Ewald
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#pragma once

// STL
#include <functional>
#include <memory>

namespace Sioc
{

// local forwards
class Container;

namespace Detail
{

enum class LifeCyclePolicy
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
        : delegate_(delegate),
          lifeCyclePolicy_(LifeCyclePolicy::Transient)
    {}

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

    void SetLifeCyclePolicy(LifeCyclePolicy lifeCyclePolicy)
    {
        lifeCyclePolicy_ = lifeCyclePolicy;
    }

private:
    std::function<std::shared_ptr<T>(const Container&)> delegate_;
    LifeCyclePolicy lifeCyclePolicy_;
    mutable std::shared_ptr<T> singleProduct_;
    mutable std::weak_ptr<T> weakSingleProduct_;
};

}
}