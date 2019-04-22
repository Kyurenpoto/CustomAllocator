#include "pch.h"

#include "../CustomAllocator/virtual_memory_wrapper.h"

#include <windows.h>

struct AddrInfo
{
	bool operator ==(const AddrInfo & other) const noexcept
	{
		return regionSize == other.regionSize && state == other.state;
	}

	SIZE_T regionSize;
	DWORD state;

	static constexpr SIZE_T pageSize = 4 * 1024;
};

namespace
{
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
	auto addr = virtual_memory_wrapper::reserve(pageCntSmall);
	
	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntSmall, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryReleased)
{
	auto addr = virtual_memory_wrapper::reserve(pageCntSmall);

	virtual_memory_wrapper::release(addr);

	auto info = getAddrInfo(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntSmall, MEM_FREE }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryCommited)
{
	auto addr = virtual_memory_wrapper::reserve(pageCntSmall);
	virtual_memory_wrapper::commit(addr, pageCntSmall);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntSmall, MEM_COMMIT }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryDecommited)
{
	auto addr = virtual_memory_wrapper::reserve(pageCntSmall);
	virtual_memory_wrapper::commit(addr, pageCntSmall);
	virtual_memory_wrapper::decommit(addr, pageCntSmall);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntSmall, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isLargeMemoryReserved)
{
	auto addr = virtual_memory_wrapper::reserve(pageCntLarge);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntLarge, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isLargeMemoryCommited)
{
	auto addr = virtual_memory_wrapper::reserve(pageCntLarge);
	virtual_memory_wrapper::commit(addr, pageCntLarge);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::decommit(addr, pageCntLarge);
	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ AddrInfo::pageSize * pageCntLarge, MEM_COMMIT }), info);
}
