// SPDX-License-Identifier: MIT
// Copyright (c) 2014 Christian Ewald

#pragma once

#include <type_traits>

namespace Sioc { namespace Detail {

template<class T, class = void>
struct IsCompleteType : std::false_type
{
};

template<class T>
struct IsCompleteType<T, std::void_t<decltype(sizeof(T))>> : std::true_type
{
};

}}
