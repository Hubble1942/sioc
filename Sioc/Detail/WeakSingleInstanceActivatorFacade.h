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