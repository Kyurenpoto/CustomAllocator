#include "stdafx.h"

#include "includes/area_allocator/area_allocator.h"
#include "includes/area_allocator/area_manager.h"

namespace
{
    constexpr std::size_t SIZE_PAGE = 4 * 1024;
    constexpr std::size_t SIZE_AREA_MIN = 64 * 1024;
    constexpr std::size_t SIZE_AREA_MAX = 4ull * 1024 * 1024 * 1024;

    std::size_t unitize(const std::size_t target, const std::size_t unit)
    {
        assert(unit > 0 && target > unit);

        return target - target % unit;
    }

    struct area_allocator
    {
        area_allocator() = default;

        ~area_allocator()
        {
            dispose();
        }

        bool isInitiatable()
        {
            return _sizeAreaMin == 0 && _sizeMemoryMax == 0;
        }

        void initiate(std::size_t sizeAreaMin, std::size_t sizeMemoryMax)
        {
            if (!isInitiatable())
                throw AreaAllocator::allocator_already_initiated{};

            _sizeAreaMin = unitize(sizeAreaMin, SIZE_PAGE);
            _sizeMemoryMax = unitize(sizeMemoryMax, _sizeAreaMin);
        }
        
        void dispose()
        {
            _sizeAreaMin = _sizeMemoryMax = 0;
        }
        
        void allocate(AreaAllocator::memory_area & target)
        {
        }
        
        void deallocate(AreaAllocator::memory_area & target)
        {
        }

    public:
        std::size_t _sizeAreaMin = 0;
        std::size_t _sizeMemoryMax = 0;
		std::size_t _sizeAllocated = 0;

        area_manager areas;
    };

    static area_allocator allocator;
}

namespace AreaAllocator
{
    void initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax)
    {
        allocator.initiate(sizeAreaMin, sizeMemoryMax);
    }

    void dispose() noexcept
    {
        allocator.dispose();
    }

    void allocate(memory_area & target)
    {
        allocator.allocate(target);
    }
    
    void deallocate(memory_area & target)
    {
        allocator.deallocate(target);
    }

	std::size_t getSizeAreaMin()
	{
		return allocator._sizeAreaMin;
	}

	std::size_t getSizeMemoryMax()
	{
		return allocator._sizeMemoryMax;
	}

	std::size_t getSizeAllocated()
	{
		return allocator._sizeAllocated;
	}
}

#include "includes/area_allocator/area_access.h"

namespace AreaAccess
{
    void constructAt(const std::size_t id,
                     const std::size_t offset,
                     const std::size_t sizeType,
                     std::function<void(void*)> constructor)
    {

    }

    void destructAt(const std::size_t id,
                    const std::size_t offset,
                    const std::size_t sizeType,
                    std::function<void(void*)> destructor)
    {

    }

    std::size_t getSizeTotal(const std::size_t id)
    {
        return 0;
    }
}
