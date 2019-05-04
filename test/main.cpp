#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "../CustomAllocator/includes/area_allocator/virtual_memory_wrapper.h"

using namespace std::chrono_literals;

MEMORY_BASIC_INFORMATION mbi;

void printAddrInfo(void * addr)
{
	VirtualQuery(addr, &mbi, sizeof(mbi));

	std::cout << "RegionSize: " << mbi.RegionSize << "\n";
	std::cout << "State: " << mbi.State << "\n";
}

int main()
{
    auto addr = virtual_memory::reserve(16);

    std::cout << "Reserve\n";
    std::this_thread::sleep_for(10s);

	printAddrInfo(addr);

    virtual_memory::release(addr);

    std::cout << "Release\n";
    std::this_thread::sleep_for(10s);

	printAddrInfo(addr);

    std::cout << "Test Complete\n";
}
