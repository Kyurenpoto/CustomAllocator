#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
    struct tmp_class :
        public virtual_memory::addr_info
    {
        bool operator == (const virtual_memory::addr_info& other) const
        {
            // The VirtualQuery function returns result of
            // scanning memory from the given address,
            // until the state of the page block changes.

            return nPage <= other.nPage && state == other.state;
        }
    };
}

class VirtualMemoryWrapperTest :
    public ::testing::TestWithParam<std::size_t>
{};

TEST_P(VirtualMemoryWrapperTest, isMemoryAllocated)
{
    auto pageCnt = GetParam();

    auto addr = virtual_memory::alloc(pageCnt);

    auto info = virtual_memory::getAddrInfo(addr);

    virtual_memory::dealloc(addr);

    ASSERT_EQ((tmp_class{
                  pageCnt,
                  virtual_memory::addr_info::addr_state::ALLOCATED }),
              info);
}

TEST_P(VirtualMemoryWrapperTest, isMemoryDeallocated)
{
    auto pageCnt = GetParam();

    auto addr = virtual_memory::alloc(pageCnt);

    virtual_memory::dealloc(addr);

    auto info = virtual_memory::getAddrInfo(addr);

    ASSERT_EQ((tmp_class{
                  pageCnt,
                  virtual_memory::addr_info::addr_state::DEALLOCATED }),
              info);
}

INSTANTIATE_TEST_CASE_P(, VirtualMemoryWrapperTest,
    ::testing::Values(16, 1024 * 1024),);
