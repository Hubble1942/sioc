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

// Uses all features of Sioc, so the templates get instantiated with C++14.

#include <Sioc/Container.h>
#include <Sioc/Lazy.h>

namespace Sioc { namespace Cpp14Check {

class A {};

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

void UseAllFeatures()
{
    Container container;

    container.RegisterType<A>().Named<A>("a").SingleInstance();
    container.RegisterInstance(std::make_shared<A>()).WeakSingleInstance();
    container.Register(TYPE(B, INJECT_NAMED(A, "a")));
    container.Register(FACTORY(std::make_shared<C>(INJECT_ALL(A), INJECT_FACTORY(A), INJECT_LAZY(A))));

    container.Resolve<B>();
    container.ResolveAll<C>();
}

} }
