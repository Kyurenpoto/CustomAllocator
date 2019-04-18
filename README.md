# CustomAllocator

Custom memory allocator with memory pool using C++

## structure

* Main Allocator(Proxy Allocator)
* Page Allocator(Free List Allocator)
* Temporary Allocator(Stack Allocator)
  * Linear Allocator
* Reusable Allocator(Pool Allocator)
  * Small Pool Allocator(with Look-Aside Array)
  * Large Pool Allocator(Stack Allocator)
