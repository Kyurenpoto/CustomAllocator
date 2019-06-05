#include "stdafx.h"

#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;
}

void* virtual_memory::alloc(std::size_t nPage) noexcept
{
    void * addr = VirtualAlloc(nullptr, nPage * PAGE_SIZE,
                              MEM_COMMIT, PAGE_READWRITE);

    assert(addr != nullptr);

    return addr;
}

void virtual_memory::dealloc(void * addr) noexcept
{
    assert(VirtualFree(addr, 0, MEM_RELEASE));
}

namespace
{
    virtual_memory::addr_info::addr_state stateWin2Enum(DWORD state) noexcept
    {
        switch (state)
        {
        case MEM_RESERVE:
        case MEM_COMMIT:
            return virtual_memory::addr_info::addr_state::ALLOCATED;
        case MEM_FREE:
        default:
            return virtual_memory::addr_info::addr_state::DEALLOCATED;
        }
    }
}

virtual_memory::addr_info virtual_memory::getAddrInfo(void * addr) noexcept
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(addr, &mbi, sizeof(mbi));

    return addr_info{ mbi.RegionSize / PAGE_SIZE, stateWin2Enum(mbi.State) };
}
