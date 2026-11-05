// SPDX-License-Identifier: MIT
// Copyright (c) 2018 Christian Ewald

#include "TestHelpers/SomeClasses.h"

#include <Sioc/Container.h>
#include <Sioc/Lazy.h>
#include <gtest/gtest.h>

namespace Sioc {

using namespace TestHelpers;

namespace {

class LazyAHolder
{
public:
    explicit LazyAHolder(const Lazy<A>& a) : a_(a) {}

    Lazy<A> a_;
};

}

TEST(LazyTest, ActivatorIsNotCalledBeforeFirstAccess)
{
    int activations = 0;

    Lazy<A> sut([&activations] {
        ++activations;
        return std::make_shared<A>();
    });

    EXPECT_FALSE(sut.IsActivated());
    EXPECT_EQ(0, activations);
}

TEST(LazyTest, GetActivatesOnlyOnce)
{
    int activations = 0;

    Lazy<A> sut([&activations] {
        ++activations;
        return std::make_shared<A>();
    });

    const auto& get1 = sut.Get();
    const auto& get2 = sut.Get();

    EXPECT_TRUE(sut.IsActivated());
    EXPECT_EQ(1, activations);
    EXPECT_NE(nullptr, get1);
    EXPECT_EQ(get1, get2);
}

TEST(LazyTest, InjectLazyResolvesOnFirstAccess)
{
    Container sut;

    sut.RegisterType<A>().SingleInstance();
    sut.Register(TYPE(LazyAHolder, INJECT_LAZY(A)));

    auto holder = sut.Resolve<LazyAHolder>();

    EXPECT_FALSE(holder->a_.IsActivated());
    EXPECT_EQ(sut.Resolve<A>(), holder->a_.Get());
}

TEST(LazyTest, InjectLazyWithinFactory)
{
    Container sut;

    sut.RegisterType<A>().SingleInstance();
    sut.Register(FACTORY(std::make_shared<LazyAHolder>(INJECT_LAZY(A))));

    auto holder = sut.Resolve<LazyAHolder>();

    EXPECT_FALSE(holder->a_.IsActivated());
    EXPECT_EQ(sut.Resolve<A>(), holder->a_.Get());
}

}
