#pragma once

namespace AreaAllocator
{
    struct area_info
    {
        template<class T, class... Args>
        void construct(const Args&& ... args);

        template<class T>
        void destruct();

        virtual std::size_t getSizeUsed() const noexcept = 0;
        std::size_t getSizeTotal() const noexcept;

        std::size_t getAreaId() const noexcept;

    protected:
        area_info(std::size_t areaId);

        template<class T, class... Args>
        void constructAt(const size_t offset, const Args&& ... args);

        template<class T>
        void destructAt(const size_t offset);

        std::size_t _areaId;
    };
}
