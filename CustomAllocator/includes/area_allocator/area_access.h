#pragma once

#include <cstddef>
#include <functional>

namespace area_access
{
    void constructAt(const std::size_t id,
                     const std::size_t offset,
                     const std::size_t sizeType,
                     std::function<void(void*)> constructor);
    void destructAt(const std::size_t id,
                    const std::size_t offset,
                    const std::size_t sizeType,
                    std::function<void(void*)> destructor);
    
    std::size_t getSizeTotal(const std::size_t id);
}