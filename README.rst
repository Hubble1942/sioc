Welcome to Sioc - The Simple IoC Container
==========================================

Yet another IoC container for C++

The bullet list:

* Header only
* Requires C++17
* No dependencies besides the standard library
* Some ideas borrowed from `Autofac <http://autofac.org/>`_ and `Hypodermic <https://github.com/ybainier/Hypodermic>`_
* Tested with GCC

Main Goals
----------

* Keep it simple
* Provide all features I currently require at work
* Be mainly finished after 4 evenings
* Keep it simple

Usage
-----

To start using Sioc, you will need to include it:

.. code:: cpp

    #include <Sioc/Container.h>

Create an instance of the Container:

.. code:: cpp

    Sioc::Container container;
    
And register some types:

.. code:: cpp

    container.RegisterType<DefaultConstructable>();
    container.RegisterType<NonDefaultCtor>([](const Container&) { return std::make_shared<NonDefaultCtor>(42); });
    container.RegisterType<Derived>().Named<Middle>("Foo").As<Base>().SingleInstance();
    container.RegisterType<BaseHolder>(CREATE(std::make_shared<BaseHolder>(INJECT(Base)))).WeakSingleInstance();
    
Now you're ready to resolv'em:

.. code:: cpp

    auto a = container.Resolve<DefaultConstructable>();
    auto b = container.ResolveNamed<Middle>("Foo");
    auto c = container.ResolveAll<BaseHolder>();

Have a look at the tests for further examples.

Testing
-------

To build and run the tests, you'll need CMake >= 3.19::

    ~/Sioc$ mkdir build
    ~/Sioc/build$ cd build
    ~/Sioc/build$ cmake ..
    ~/Sioc/build$ make
    ~/Sioc/build$ test/SiocTest


License
-------

Sioc is released under the `MIT License <http://www.opensource.org/licenses/MIT>`_.