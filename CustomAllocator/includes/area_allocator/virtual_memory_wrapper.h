#pragma once

#include <cstddef>

namespace virtual_memory
{
    void *    alloc(std::size_t nPage);
    void      dealloc(void * addr);

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

    addr_info getAddrInfo(void * addr);
}
