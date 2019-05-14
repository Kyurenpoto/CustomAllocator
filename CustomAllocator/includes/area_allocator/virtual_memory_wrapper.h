#pragma once

#include <cstddef>

namespace virtual_memory
{
    void *    alloc(std::size_t nPage);
    void      dealloc(void * addr);

    struct AddrInfo
    {
        std::size_t nPage;

        enum class AddrState : bool
        {
            DEALLOCATED,
            ALLOCATED
        };

        AddrState state;
    };

    AddrInfo getAddrInfo(void * addr);
}
