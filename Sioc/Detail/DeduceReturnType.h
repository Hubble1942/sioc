// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <type_traits>

namespace Sioc { class Container; }

namespace Sioc { namespace Detail {

/// The type of the instance whose `std::shared_ptr` a delegate returns.
template<typename D>
struct DeduceReturnType
{
    using Type = typename std::invoke_result_t<D, const Container&>::element_type;
};

}}
