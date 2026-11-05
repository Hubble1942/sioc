// The MIT License(MIT)
//
// Copyright(c) 2018 Christian Ewald
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

#include <functional>
#include <memory>

namespace Sioc
{

/// A service that is resolved on the first access.
template<class T>
class Lazy
{
public:
    using Activator = std::function<std::shared_ptr<T>()>;

    explicit Lazy(Activator activator)
        : activator_(activator)
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
