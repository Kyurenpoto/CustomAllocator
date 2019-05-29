#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"
#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
    constexpr std::size_t SIZE_CACHE_LINE = 64;
    constexpr std::size_t SIZE_PAGE_MIN = 4 * 1024;

    void initMemory(void * memory, const std::size_t size)
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

    struct area_header
    {
        std::size_t _idArea;
        std::size_t _cntChunkTotal;
        std::size_t _cntChunkUsed;
        area_header * _nextArea;
        area_header * _prevArea;
        chunk_header * _activeChunk;
        chunk_header * _inactiveChunk;
    };

    struct area_manage_header
    {
        std::size_t _idManage;
        std::size_t _cntAreaUsed;
        area_manage_header * _nextManage;
        area_manage_header * _prevManage;
        area_header * _activeArea;
        area_header * _inactiveArea;

        static constexpr std::size_t SIZE = 2 * 1024 * 1024;
        static constexpr std::size_t CNT_PAGE = SIZE / SIZE_PAGE_MIN;
        static constexpr std::size_t CNT_CHUNK = SIZE / SIZE_CACHE_LINE - 3;

        area_manage_header(std::size_t id) :
            _idManage{ id },
            _cntAreaUsed{0},
            _nextManage{this},
            _prevManage{this},
            _activeArea{ reinterpret_cast<area_header*>(
                             reinterpret_cast<cache_line*>(this) + 1) },
            _inactiveArea{ reinterpret_cast<area_header*>(
                               reinterpret_cast<cache_line*>(this) + 2) }
        {

        }

        ~area_manage_header() = default;

        static void initialize(void * memory, std::size_t id)
        {
            initMemory(memory, area_manage_header::CNT_CHUNK + 3);

            new(memory) area_manage_header{ id };
        }

        static void dispose(void * memory)
        {
            reinterpret_cast<area_manage_header *>(memory)->
                ~area_manage_header();

            initMemory(memory, area_manage_header::CNT_CHUNK + 3);
        }

        void addActiveArea(std::size_t idArea)
        {
            assert(idArea < area_manage_header::CNT_CHUNK);
        }

        void removeActiveArea(std::size_t idArea)
        {
            assert(idArea < area_manage_header::CNT_CHUNK);
        }

        void addInactiveArea(std::size_t idArea)
        {
            assert(idArea < area_manage_header::CNT_CHUNK);
        }

        void removeInactiveArea(std::size_t idArea)
        {
            assert(idArea < area_manage_header::CNT_CHUNK);
        }
    };
}

area_manager::~area_manager()
{
    dispose();
}

void area_manager::initialize(const uint32_t size)
{
}

void area_manager::initialize()
{
    _areas = virtual_memory::alloc(area_manage_header::CNT_PAGE);

    area_manage_header::initialize(_areas, 0);
}

void area_manager::dispose()
{
    area_manage_header::dispose(_areas);

    virtual_memory::dealloc(_areas);
}

uint32_t area_manager::allocate(std::size_t nPage)
{
    assert(_size > 0);

    return 0;
}

void area_manager::deallocate(uint32_t id)
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
