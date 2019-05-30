#include "stdafx.h"

#include "includes/area_allocator/area_allocator.h"
#include "includes/area_allocator/area_manager.h"

namespace
{
    constexpr std::size_t SIZE_PAGE = 4 * 1024;
    constexpr std::size_t SIZE_AREA_MIN = 64 * 1024;

    std::size_t unitize(const std::size_t target, const std::size_t unit) noexcept
    {
        assert(unit > 0 && target > unit);

        return target - target % unit;
    }

    struct area_allocator_impl
    {
        area_allocator_impl() = default;

        ~area_allocator_impl()
        {
            dispose();
        }

        bool isInitiatable()
        {
            return _sizeAreaMin == 0 && _sizeMemoryMax == 0;
        }

        void initialize(std::size_t sizeAreaMin, std::size_t sizeMemoryMax)
        {
            if (!isInitiatable())
                throw area_allocator::allocator_already_initiated{};

            _sizeAreaMin = unitize(sizeAreaMin, SIZE_PAGE);
            _sizeMemoryMax = unitize(sizeMemoryMax, _sizeAreaMin);

            areas.initialize();
        }
        
        void dispose() noexcept
        {
            _sizeAreaMin = _sizeMemoryMax = 0;

            areas.dispose();
        }

    public:
        std::size_t _sizeAreaMin = 0;
        std::size_t _sizeMemoryMax = 0;
		std::size_t _sizeAllocated = 0;

        area_manager areas;
    };

    static area_allocator_impl allocator;
}

namespace area_allocator
{
    void initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax)
    {
        allocator.initialize(sizeAreaMin, sizeMemoryMax);
    }

    void dispose() noexcept
    {
        allocator.dispose();
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

namespace area_access
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
