// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Christian Ewald

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
    using IfConvertible = std::enable_if_t<std::is_convertible_v<T*, U*>>;

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
