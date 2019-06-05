#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"
#include "includes/area_allocator/virtual_memory_wrapper.h"

#include <array>
#include <variant>

namespace
{
    constexpr std::size_t SIZE_CACHE_LINE = 64;
    constexpr std::size_t SIZE_PAGE_MIN = 4 * 1024;

    void initMemory(void * memory, const std::size_t size) noexcept
    {
        assert(memory != nullptr);
        assert(virtual_memory::getAddrInfo(memory).nPage >= size);

        std::memset(memory, 0, size);
    }

    struct cache_line
    {
        char data[SIZE_CACHE_LINE];
    };

    struct chunk_header
    {
        std::size_t _idChunk;
        std::size_t _sizeAlign;
        chunk_header * _nextChunk;
        chunk_header * _prevChunk;
    };

    struct index_header;

    struct area_header
    {
        std::size_t _idArea;
        std::size_t _cntChunkTotal;
        std::size_t _cntChunkUsed;
        index_header * _index;
    };

    using memory_area = cache_line;

    struct index_header
    {
        area_header * _area;
        index_header * _root;
        uint32_t _idArea;
        uint32_t _parent;
        uint32_t _left;
        uint32_t _right;
    };

    struct manage_header
    {
        std::size_t _idManage;
        uint32_t _cntAreaUsed;
        uint32_t _cntIndexUsed;
        manage_header * _nextManage;
        manage_header * _prevManage;
    };

    struct manage_area
    {
        static constexpr std::size_t SIZE = 2 * 1024 * 1024;
        static constexpr std::size_t CNT_PAGE = SIZE / SIZE_PAGE_MIN;
        static constexpr std::size_t CNT_CHUNK = SIZE / SIZE_CACHE_LINE * 2 - 1;

        static void initialize(manage_area * area, std::size_t id) noexcept
        {
            initMemory(area, SIZE);

            manage_header * header = &area->_header;

            header->_idManage = id;
            header->_nextManage = header->_prevManage = header;
        }

        static void dispose(manage_area * area) noexcept
        {
            initMemory(area, SIZE);
        }

        bool isOverflow() const noexcept
        {
            return false;
        }

        bool isUnderflow() const noexcept
        {
            return false;
        }

        uint32_t addArea(const memory_area * area) const noexcept
        {
            assert(!isOverflow());

            return 0;
        }

        void removeArea(const uint32_t id) const noexcept
        {
            assert(!isUnderflow());
        }

        memory_area * findArea(const uint32_t id) const noexcept
        {
            assert(!isUnderflow());

            return nullptr;
        }

        manage_header _header;
        std::array<index_header, CNT_CHUNK> _chunks;
    };
}

area_manager::~area_manager() noexcept
{
    dispose();
}

void area_manager::initialize() noexcept
{
    assert(_areas == nullptr);

    _areas = virtual_memory::alloc(manage_area::CNT_PAGE);

    manage_area::initialize(static_cast<manage_area*>(_areas), 0);
}

void area_manager::dispose() noexcept
{
    assert(_areas != nullptr);

    manage_area::dispose(static_cast<manage_area*>(_areas));

    virtual_memory::dealloc(_areas);
}

uint32_t area_manager::allocate(std::size_t nPage) noexcept
{
    assert(_size > 0);

    return 0;
}

void area_manager::deallocate(uint32_t id) noexcept
{
    assert(_size > 0);

    _sizeArea[id] = 1;
}

const std::size_t area_manager::getSizeArea(const uint32_t id) const noexcept
{
    assert(_size > 0);
    assert(id < _size);

    return _sizeArea[id];
}

bool area_manager::isInitialState() const noexcept
{
    assert(_size > 0);

    return _idNext[1] == 1;
}
