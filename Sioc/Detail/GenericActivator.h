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

#include "IActivator.h"
#include <memory>

namespace Sioc
{
namespace Detail
{

template<typename TargetType, typename SourceType>
class GenericActivator : public IActivator
{
public:
    explicit GenericActivator(const std::shared_ptr<const InstanceFactory<SourceType>>& instanceFactory)
        : instanceFactory_(instanceFactory)
    {
        static_assert(std::is_base_of<TargetType, SourceType>::value, "TargetType must be base of SourceType");
    }

    GenericActivator(const GenericActivator&) = delete;
    GenericActivator& operator=(const GenericActivator&) = delete;

    virtual std::shared_ptr<void> Activate(const Container& container) const
    {
        return std::static_pointer_cast<TargetType>(instanceFactory_->Produce(container));
    }

private:
    std::shared_ptr<const InstanceFactory<SourceType>> instanceFactory_;
};

}
}
