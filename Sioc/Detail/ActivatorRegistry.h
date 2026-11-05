// The MIT License(MIT)
//
// Copyright(c) 2014 Christian Ewald
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

#include "TypeInfo.h"

#include <memory>
#include <unordered_map>
#include <list>

namespace Sioc { namespace Detail {

class IActivator;

/// Maps the identifier of each registration to its activators.
class ActivatorRegistry
{
public:
    typedef std::list<std::shared_ptr<const Detail::IActivator>> Activators;

private:
    typedef std::unordered_map<Detail::TypeInfo::IdType, Activators, Detail::TypeInfo::IdHash> Registry;

public:
    ActivatorRegistry() = default;
    ActivatorRegistry(const ActivatorRegistry&) = delete;
    ActivatorRegistry& operator=(const ActivatorRegistry&) = delete;

    void Insert(const TypeInfo::IdType& id, const std::shared_ptr<const IActivator>& activator)
    {
        registry_[id].push_back(activator);
    }

    /// Returns an empty list for an identifier nothing is registered for.
    const Activators& GetAllForType(const TypeInfo::IdType& id) const
    {
        auto found = registry_.find(id);

        if (found != registry_.end())
        {
            return found->second;
        }

        return empty_;
    }

private:
    Registry registry_;
    Activators empty_;
};

} }
