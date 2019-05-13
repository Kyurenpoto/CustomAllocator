#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/virtual_memory_wrapper.h"

#include <windows.h>

namespace
{
    constexpr SIZE_T pageSize = 4 * 1024;
	constexpr SIZE_T pageCntSmall = 16;
	constexpr SIZE_T pageCntLarge = 1024 * 1024;

    struct tmp_class :
        public virtual_memory::AddrInfo
    {
        bool operator == (const virtual_memory::AddrInfo& other) const
        {
            // The VirtualQuery function returns result of
            // scanning memory from the given address,
            // until the state of the page block changes.

            return nPage <= other.nPage && state == other.state;
        }
    };
}

// TODO: Value-Parameterized Tests using gtest

TEST(VirtualMemoryWrapperTest, isMemoryAllocated)
{
    auto addr = virtual_memory::alloc(pageCntSmall);

    auto info = virtual_memory::getAddrInfo(addr);

    virtual_memory::dealloc(addr);

    ASSERT_EQ((tmp_class{
                  pageCntSmall,
                  virtual_memory::AddrInfo::AddrState::COMMIT }),
              info);
}

TEST(VirtualMemoryWrapperTest, isMemoryDeallocated)
{
    auto addr = virtual_memory::alloc(pageCntSmall);

    virtual_memory::dealloc(addr);

    auto info = virtual_memory::getAddrInfo(addr);

    ASSERT_EQ((tmp_class{
                  pageCntSmall,
                  virtual_memory::AddrInfo::AddrState::FREE }),
              info);
}

TEST(VirtualMemoryWrapperTest, isMemoryAllocatedLarge)
{
    auto addr = virtual_memory::alloc(pageCntLarge);

    auto info = virtual_memory::getAddrInfo(addr);

    virtual_memory::dealloc(addr);

    ASSERT_EQ((tmp_class{
                  pageCntLarge,
                  virtual_memory::AddrInfo::AddrState::COMMIT }),
              info);
}

TEST(VirtualMemoryWrapperTest, isMemoryDeallocatedLarge)
{
    auto addr = virtual_memory::alloc(pageCntLarge);

    virtual_memory::dealloc(addr);

    auto info = virtual_memory::getAddrInfo(addr);

    ASSERT_EQ((tmp_class{
                  pageCntLarge,
                  virtual_memory::AddrInfo::AddrState::FREE }),
              info);
}
