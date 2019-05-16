#pragma once

#include <cstddef>
#include <functional>

namespace AreaAccess
{
    void ConstructAt(const std::size_t id,
                     const std::size_t offset,
                     const std::size_t sizeType,
                     std::function<void(void*)> constructor);

    void DestructAt(const std::size_t id,
                    const std::size_t offset,
                    const std::size_t sizeType,
                    std::function<void(void*)> destructor);
}