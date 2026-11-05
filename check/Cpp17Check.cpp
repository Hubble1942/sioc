// SPDX-License-Identifier: MIT
// Copyright (c) 2026 Christian Ewald

// Uses all features of Sioc, so the templates get instantiated with C++17.

#include <Sioc/Container.h>
#include <Sioc/Lazy.h>

namespace Sioc { namespace Cpp17Check {

namespace {

class A
{
};

class B
{
public:
    explicit B(const std::shared_ptr<A>&) {}
};

class C
{
public:
    C(const std::vector<std::shared_ptr<A>>&, const std::function<std::shared_ptr<A>()>&, const Lazy<A>&) {}
};

class D
{
public:
    D(A& a, std::weak_ptr<A> weak, std::shared_ptr<A> shared)
        : a_(&a), weak_(std::move(weak)), shared_(std::move(shared))
    {
    }

    A* a_;
    std::weak_ptr<A> weak_;
    std::shared_ptr<A> shared_;
};

}

// NOLINTNEXTLINE(misc-use-internal-linkage): unused, an internal function would be a warning
void UseAllFeatures()
{
    Container container;

    container.RegisterType<A>().Named<A>("a").SingleInstance();
    container.RegisterInstance(std::make_shared<A>()).WeakSingleInstance();
    container.Register(TYPE(B, INJECT_NAMED(A, "a")));
    container.Register(FACTORY(std::make_shared<C>(INJECT_ALL(A), INJECT_FACTORY(A), INJECT_LAZY(A))));
    container.Register(TYPE(D, INJECT(A), INJECT(A), INJECT(A)));

    container.Resolve<B>();
    container.ResolveAll<C>();
    container.Resolve<D>();
}

}}
