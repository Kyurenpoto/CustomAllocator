#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/virtual_memory_wrapper.h"

#include <windows.h>

struct AddrInfo
{
	bool operator ==(const AddrInfo & other) const noexcept
	{
		return regionSize == other.regionSize && state == other.state;
	}

	SIZE_T regionSize;
	DWORD state;
};

namespace
{
    constexpr SIZE_T pageSize = 4 * 1024;
	constexpr SIZE_T pageCntSmall = 16;
	constexpr SIZE_T pageCntLarge = 1024 * 1024;
}

AddrInfo getAddrInfo(void * addr)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(addr, &mbi, sizeof(mbi));

	return AddrInfo{ mbi.RegionSize, mbi.State };
}

TEST(VirtualMemoryWrapperTest, isMemoryReserved)
{
	auto addr = virtual_memory::reserve(pageCntSmall);
	
	auto info = getAddrInfo(addr);

	virtual_memory::release(addr);

	ASSERT_EQ((AddrInfo{ pageSize * pageCntSmall, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryReleased)
{
	auto addr = virtual_memory::reserve(pageCntSmall);

	virtual_memory::release(addr);

    auto info = getAddrInfo(addr);

	ASSERT_EQ(MEM_FREE, info.state);
}

TEST(VirtualMemoryWrapperTest, isMemoryCommited)
{
	auto addr = virtual_memory::reserve(pageCntSmall);
	virtual_memory::commit(addr, pageCntSmall);

	auto info = getAddrInfo(addr);

	virtual_memory::release(addr);

	ASSERT_EQ((AddrInfo{ pageSize * pageCntSmall, MEM_COMMIT }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryDecommited)
{
	auto addr = virtual_memory::reserve(pageCntSmall);
	virtual_memory::commit(addr, pageCntSmall);
	virtual_memory::decommit(addr, pageCntSmall);

	auto info = getAddrInfo(addr);

	virtual_memory::release(addr);

	ASSERT_EQ((AddrInfo{ pageSize * pageCntSmall, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isLargeMemoryReserved)
{
	auto addr = virtual_memory::reserve(pageCntLarge);

	auto info = getAddrInfo(addr);

	virtual_memory::release(addr);

	ASSERT_EQ((AddrInfo{ pageSize * pageCntLarge, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isLargeMemoryCommited)
{
	auto addr = virtual_memory::reserve(pageCntLarge);
	virtual_memory::commit(addr, pageCntLarge);

	auto info = getAddrInfo(addr);

	virtual_memory::decommit(addr, pageCntLarge);
	virtual_memory::release(addr);

	ASSERT_EQ((AddrInfo{ pageSize * pageCntLarge, MEM_COMMIT }), info);
}
