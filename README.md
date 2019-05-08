# CustomAllocator

Custom memory allocator with memory pool using C++

## dependency

* MSVC 16

## structure

* Main Allocator(Proxy Allocator)
  * Provide allocating interfaces
  * Benchmark memory usage
  * Top abstract layer
* Level Allocator(Stack Allocator)
  * Push low level first
* Frame Buffer(Linear Allocator)
  * Write from initial pointer each frame
* Stream Buffer(Ring Allocator)
  * Structed by circular queue
* Object Buffer(Pool Allocator)
  * Use look-aside array for fast search
