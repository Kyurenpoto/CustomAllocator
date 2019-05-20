#pragma once

#include <vector>
#include <functional>

struct area_manager
{
    area_manager() = default;
    area_manager(const area_manager &) = delete;
    area_manager(area_manager &&) = delete;
    area_manager & operator = (const area_manager &) = delete;
    area_manager & operator = (area_manager &&) = delete;
    ~area_manager();

    void initialize(const uint32_t size);
    void dispose();

    uint32_t allocate(std::size_t nPage);
    void deallocate(uint32_t id);
    void constructAt(const std::size_t id,
                     const std::size_t offset,
                     const std::size_t sizeType,
                     std::function<void(void*)> constructor);
    void destructAt(const std::size_t id,
                    const std::size_t offset,
                    const std::size_t sizeType,
                    std::function<void(void*)> destructor);

    const std::size_t getSizeArea(const uint32_t id) const noexcept;

private:
    bool isInitialState() const noexcept;

private:
    uint32_t _size = 0;

    std::vector<uint32_t> _idNext;
    std::vector<uint32_t> _idPrev;

    std::vector<std::size_t> _sizeArea;
    std::vector<void *> _locArea;
};
