#include "stdafx.h"

#include "area_allocator.h"

namespace
{
    constexpr std::size_t SIZE_PAGE = 4 * 1024;
    constexpr std::size_t SIZE_AREA_MIN = 64 * 1024;
    constexpr std::size_t SIZE_AREA_MAX = 4ull * 1024 * 1024 * 1024;

    std::size_t unitize(const std::size_t unit, const std::size_t target)
    {
        assert(unit > 0 &&
               target > 0);

        return target - target % unit;
    }

    struct area_allocator
    {
        area_allocator() = default;

        ~area_allocator()
        {
            dispose();
        }

        AreaAllocator::AreaResult initiate(
            std::size_t sizeAreaMin,
            std::size_t sizeMemoryMax)
        {
            try
            {
                assert(_sizeAreaMin == 0 && _sizeMemoryMax == 0);
            }
            catch (...)
            {
                return AreaAllocator::AreaResult::ALREADY_INITIATED;
            }

            try
            {
                _sizeAreaMin = unitize(sizeAreaMin, SIZE_PAGE);
                _sizeMemoryMax = unitize(sizeMemoryMax, SIZE_PAGE);
            }
            catch(...)
            {
                return AreaAllocator::AreaResult::UNDEFINED;
            }

            try
            {
                _sizeMemoryMax = unitize(_sizeMemoryMax, _sizeAreaMin);
                
                assert(sizeMemoryMax > sizeAreaMin);

                return AreaAllocator::AreaResult::SUCCESSED;
            }
            catch(...)
            {
                return AreaAllocator::AreaResult::UNDEFINED;
            }
        }
        
        AreaAllocator::AreaResult dispose()
        {
            return AreaAllocator::AreaResult::SUCCESSED;
        }
        
        AreaAllocator::AreaResult allocate(
            AreaAllocator::memory_area & target)
        {
            return AreaAllocator::AreaResult::SUCCESSED;
        }
        
        AreaAllocator::AreaResult deallocate(
            AreaAllocator::memory_area & target)
        {
            return AreaAllocator::AreaResult::SUCCESSED;
        }

    private:
        std::size_t _sizeAreaMin = 0;
        std::size_t _sizeMemoryMax = 0;
    };

    static area_allocator allocator;
}

namespace AreaAllocator
{
    AreaResult Initiate(const std::size_t sizeAreaMin,
                        const std::size_t sizeMemoryMax)
    {
        return allocator.initiate(sizeAreaMin, sizeMemoryMax);
    }

    AreaResult Dispose()
    {
        return allocator.dispose();
    }

    AreaResult Allocate(memory_area & target)
    {
        return allocator.allocate(target);
    }
    
    AreaResult Deallocate(memory_area & target)
    {
        return allocator.deallocate(target);
    }
}
