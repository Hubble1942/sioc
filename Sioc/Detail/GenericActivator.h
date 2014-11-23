#pragma once

// local
#include "IActivator.h"

// STL
#include <functional>

// boost
#include <boost/noncopyable.hpp>

namespace Sioc
{
namespace Detail
{

template<typename T>
class GenericActivator : public IActivator, private boost::noncopyable
{
public:
    explicit GenericActivator(std::function<std::shared_ptr<T>(const Container&)> delegate)
        : delegate_(delegate)
    {}

    virtual std::shared_ptr<void> Activate(const Container& c) const
    {
        return delegate_(c);
    }

private:
    std::function<std::shared_ptr<T>(const Container&)> delegate_;
};

}
}