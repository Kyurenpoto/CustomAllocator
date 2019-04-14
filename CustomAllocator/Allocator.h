#pragma once

#include <cassert>

struct Allocator
{
	Allocator(size_t size, void* start) :
		_start{ start },
		_size{ size }
	{}

	virtual ~Allocator()
	{
		assert(_num_allocators == 0 && _used_memory == 0);

		_start = nullptr;
		_size = 0;
	}

    virtual void* allocate(size_t size) = 0;
    
    virtual void deallocate(void* p) = 0;

    void* getStart() const noexcept
    {
        return _start;
    }

    size_t getSize() const noexcept
    {
        return _size;
    }
    
    size_t getUsedMemory() const noexcept
    {
        return _used_memory;
    }
    
    size_t getNumAllocators() const noexcept
    {
        return _num_allocators;
    }

protected:
	void* _start;
	size_t _size;

	size_t _used_memory{ 0 };
	size_t _num_allocators{ 0 };
};
