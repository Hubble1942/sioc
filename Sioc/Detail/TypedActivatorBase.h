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

namespace Sioc
{

// forwards
class Container;

namespace Detail
{

/// <summary>
/// Generic interface for activators for a specific type.
/// </summary>
template<typename T>
class TypedActivatorBase : public IActivator
{
public:
    /// <summary>
    /// Activates the embedded instance.
    /// </summary>
    /// <param name="container">The ioc container.</param>
    /// <returns>The activated instance.</returns>
    virtual std::shared_ptr<void> Activate(const Container& container) const
    {
        return std::static_pointer_cast<void>(ActivateTyped(container));
    }

    /// <summary>
    /// Activates the embedded instance.
    /// </summary>
    /// <param name="container">The ioc container.</param>
    /// <returns>The activated instance.</returns>
    virtual std::shared_ptr<T> ActivateTyped(const Container& container) const = 0;
};

}
}
