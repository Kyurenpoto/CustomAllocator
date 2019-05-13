#include "stdafx.h"

#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;
}

void* virtual_memory::alloc(std::size_t nPage)
{
    void * addr = VirtualAlloc(nullptr, nPage * PAGE_SIZE,
                              MEM_COMMIT, PAGE_READWRITE);

    assert(addr != nullptr);

    return addr;
}

void virtual_memory::dealloc(void * addr)
{
    assert(VirtualFree(addr, 0, MEM_RELEASE));
}

namespace
{
    virtual_memory::AddrInfo::AddrState stateWin2Enum(DWORD state)
    {
        switch (state)
        {
        case MEM_FREE:
            return virtual_memory::AddrInfo::AddrState::FREE;
        case MEM_RESERVE:
            return virtual_memory::AddrInfo::AddrState::RESERVE;
        case MEM_COMMIT:
            return virtual_memory::AddrInfo::AddrState::COMMIT;
        default:
            return virtual_memory::AddrInfo::AddrState::FREE;
        }
    }
}

virtual_memory::AddrInfo virtual_memory::getAddrInfo(void * addr)
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(addr, &mbi, sizeof(mbi));

    return AddrInfo{ mbi.RegionSize / PAGE_SIZE, stateWin2Enum(mbi.State) };
}
