#pragma once

#include <cstddef>

namespace virtual_memory
{
    void *    alloc(std::size_t nPage) noexcept;
    void      dealloc(void * addr)     noexcept;

    struct addr_info
    {
        std::size_t nPage;

        enum class addr_state : bool
        {
            DEALLOCATED,
            ALLOCATED
        };

        addr_state state;
    };

    addr_info getAddrInfo(void * addr) noexcept;
}
