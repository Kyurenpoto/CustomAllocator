#include "pch.h"

#include "../CustomAllocator/virtual_memory_wrapper.h"

#include <windows.h>

struct AddrInfo
{
	AddrInfo(const SIZE_T regionSize_, const DWORD state_) noexcept :
		regionSize{ regionSize_ },
		state{ state_ }
	{}

	AddrInfo(AddrInfo && other) noexcept :
		regionSize{ other.regionSize },
		state{ other.state }
	{
		other.regionSize = 0;
		other.state = 0;
	}

	bool operator ==(const AddrInfo & other) const noexcept
	{
		return regionSize == other.regionSize && state == other.state;
	}

	SIZE_T regionSize;
	DWORD state;
};

AddrInfo getAddrInfo(void * addr)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(addr, &mbi, sizeof(mbi));

	return AddrInfo{ mbi.RegionSize, mbi.State };
}

TEST(VirtualMemoryWrapperTest, isMemoryReserved)
{
	auto addr = virtual_memory_wrapper::reserve(16);
	
	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ 16 * 4 * 1024, MEM_RESERVE }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryReleased)
{
	auto addr = virtual_memory_wrapper::reserve(16);

	virtual_memory_wrapper::release(addr);

	auto info = getAddrInfo(addr);

	ASSERT_EQ((AddrInfo{ 16 * 4 * 1024, MEM_FREE }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryCommited)
{
	auto addr = virtual_memory_wrapper::reserve(16);
	virtual_memory_wrapper::commit(addr, 16);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ 16 * 4 * 1024, MEM_COMMIT }), info);
}

TEST(VirtualMemoryWrapperTest, isMemoryDecommited)
{
	auto addr = virtual_memory_wrapper::reserve(16);
	virtual_memory_wrapper::commit(addr, 16);
	virtual_memory_wrapper::decommit(addr, 16);

	auto info = getAddrInfo(addr);

	virtual_memory_wrapper::release(addr);

	ASSERT_EQ((AddrInfo{ 16 * 4 * 1024, MEM_RESERVE }), info);
}
