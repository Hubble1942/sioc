# Welcome to Sioc - The Simple IoC Container

Yet another IoC container for C++

The bullet list:

* Header only
* Requires C++14
* No dependencies besides the standard library
* Some ideas borrowed from [Autofac](http://autofac.org/) and [Hypodermic](https://github.com/ybainier/Hypodermic)
* Tested with GCC

## Main Goals

* Keep it simple
* Provide all features I currently require at work
* Be mainly finished after 4 evenings
* Keep it simple

## Usage

To start using Sioc, you will need to include it:

```cpp
#include <Sioc/Container.h>
```

Create an instance of the Container:

```cpp
Sioc::Container container;
```

And register some types:

```cpp
container.RegisterType<DefaultConstructable>();
container.Register([](const Sioc::Container&) { return std::make_shared<NonDefaultCtor>(42); });
container.RegisterType<Derived>().Named<Middle>("Foo").As<Base>().SingleInstance();
container.Register(TYPE(BaseHolder, INJECT(Base))).WeakSingleInstance();
```

Now you're ready to resolv'em:

```cpp
auto a = container.Resolve<DefaultConstructable>();
auto b = container.ResolveNamed<Middle>("Foo");
auto c = container.ResolveAll<BaseHolder>();
```

Have a look at the tests for further examples.

### Injection helpers

`TYPE` and `FACTORY` create the delegate passed to `Register`. Within their arguments, the
`INJECT` macros resolve the dependencies from the container:

| Macro | Result |
|---|---|
| `TYPE(type, args...)` | Creates `type` with `std::make_shared<type>(args...)` |
| `FACTORY(statement)` | Creates the instance returned by `statement` |
| `INJECT(type)` | `Sioc::Injected<type>`, converting to `std::shared_ptr`, `std::weak_ptr` or a reference |
| `INJECT_NAMED(type, name)` | `Sioc::Injected<type>` registered with `name` |
| `INJECT_ALL(type)` | `std::vector<std::shared_ptr<type>>` with all registrations of `type` |
| `INJECT_FACTORY(type)` | Function returning a `std::shared_ptr<type>` on each call |
| `INJECT_LAZY(type)` | `Sioc::Lazy<type>` resolving on first access (requires `<Sioc/Lazy.h>`) |

```cpp
container.Register(TYPE(Client, INJECT_NAMED(Middle, "Foo"), INJECT_ALL(Base), INJECT_FACTORY(Service), INJECT_LAZY(Service)));
container.Register(FACTORY(std::make_shared<BaseHolder>(INJECT(Base))));
```

`INJECT` and `INJECT_NAMED` pass the instance the way the constructor parameter asks for it: a
`std::shared_ptr` or `std::weak_ptr` if the class keeps the instance, a reference if it only uses it
while it's constructed. So `TYPE(Client, INJECT(Service))` fits both of these constructors:

```cpp
Client(std::shared_ptr<Service> service);
Client(Service& service);
```

A class that keeps the instance must take a smart pointer: for a transient registration, the
`Sioc::Injected` is the instance's only owner. Converting it to a value of the instance's type doesn't
compile, so a service isn't copied or sliced by accident. `->`, `*` and `Get()` reach the instance
itself, e.g. `FACTORY(INJECT(Factory)->Create())`.

## Testing

To build and run the tests, you'll need a C++17 compiler and CMake >= 3.19:

```sh
~/Sioc$ mkdir build
~/Sioc$ cd build
~/Sioc/build$ cmake ..
~/Sioc/build$ make
~/Sioc/build$ test/SiocTest
```

## License

Sioc is released under the [MIT License](http://www.opensource.org/licenses/MIT).
