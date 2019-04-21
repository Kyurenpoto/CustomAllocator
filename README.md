# CustomAllocator

Custom memory allocator with memory pool using C++

## dependency

* MSVC 16

## structure

* Main Allocator(Proxy Allocator)
* Page Allocator(Free List Allocator)
* Temporary Allocator(Stack Allocator)
  * Linear Allocator
* Reusable Allocator(Pool Allocator)
  * Small Pool Allocator(with Look-Aside Array)
  * Large Pool Allocator(Stack Allocator)

### Page Allocator

1. Allocate / release page-level area wrapper
   * VirtualAlloc / VirtualFree
   * Wrapping with a simple API for application
   * Configure the address and size of the area as area information objects
2. Wrapper for check specific memory area information
   * VirtualQuery
   * Used for testing purposes
3. Free List Allocator for memory area management
   * Initialization first at application startup
   * Assuming that the minimum size of the area is 10 MB, 16 GB RAM can be allocated to a maximum of 1638 areas
   * Assuming that only 1500 areas are used, the space for Free-List should be pre-allocated about 50KB
   * Provide allocation / release request API
     * Allocated / released area information objects are managed as Free-Lists, respectively
     * Uses a pointer of the area information object as a parameter and calls the wrapper API internally
