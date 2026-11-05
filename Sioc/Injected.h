// The MIT License(MIT)
//
// Copyright(c) 2026 Christian Ewald
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

#include <memory>
#include <type_traits>
#include <utility>

namespace Sioc
{

/// A resolved instance as `INJECT` passes it on: it converts to what the parameter it is passed to asks
/// for, the `std::shared_ptr` or `std::weak_ptr` if the receiver keeps the instance, a reference if it
/// only uses it.
///
/// A receiver that keeps the instance must take a smart pointer: for a transient registration, the
/// `Injected` is the instance's only owner. Converting to a value of the instance's type is deleted, so a
/// service is never copied or sliced by accident.
template<class T>
class Injected
{
    template<class U>
    using IfConvertible = std::enable_if_t<std::is_convertible<T*, U*>::value>;

public:
    using element_type = T;

    explicit Injected(std::shared_ptr<T> instance)
        : instance_(std::move(instance))
    {}

    template<class U, class = IfConvertible<U>>
    // NOLINTNEXTLINE(*-explicit-constructor): the parameter it's passed to picks the conversion
    operator std::shared_ptr<U>() const&
    {
        return instance_;
    }

    template<class U, class = IfConvertible<U>>
    // NOLINTNEXTLINE(*-explicit-constructor): the parameter it's passed to picks the conversion
    operator std::shared_ptr<U>() &&
    {
        return std::move(instance_);
    }

    template<class U, class = IfConvertible<U>>
    // NOLINTNEXTLINE(*-explicit-constructor): the parameter it's passed to picks the conversion
    operator std::weak_ptr<U>() const
    {
        return instance_;
    }

    template<class U, class = IfConvertible<U>>
    // NOLINTNEXTLINE(*-explicit-constructor): the parameter it's passed to picks the conversion
    operator U&() const
    {
        return *instance_;
    }

    template<class U, class = IfConvertible<U>>
    operator U() const = delete;

    const std::shared_ptr<T>& Get() const
    {
        return instance_;
    }

    T& operator*() const
    {
        return *instance_;
    }

    T* operator->() const
    {
        return instance_.get();
    }

    /// `false` if the type wasn't registered.
    explicit operator bool() const
    {
        return static_cast<bool>(instance_);
    }

private:
    std::shared_ptr<T> instance_;
};

}
