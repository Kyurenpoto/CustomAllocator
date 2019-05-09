# CustomAllocator

Custom memory allocator with memory pool using C++

## dependency

* MSVC 16

## structure

* Bottom Abstract Layer
  * Virtual Memory Allocation API Wrapper
    * Reduce dependency about OS API
* Middle Abstract Layer
  * Area Allocator
    * Provide allocating interfaces
    * Benchmark memory usage
* Top Abstract Layer
  * Level Allocator(Stack Allocator)
    * Push low level first
  * Frame Buffer(Linear Allocator)
    * Write from initial pointer each frame
  * Stream Buffer(Ring Allocator)
    * Structed by circular queue
  * Object Buffer(Pool Allocator)
    * Use look-aside array for fast search
