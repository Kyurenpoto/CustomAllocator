#pragma once

#include <cstddef>
#include <functional>
#include <new>

namespace AreaAllocator
{
    struct area_info
    {
        template<class T, class... Args>
        void construct(const Args&& ... args)
        {
            constructImpl(sizeof(T),
                          [](void * addr) { new(addr) T{ args... }; });
        }

        template<class T>
        void destruct()
        {
            destructImpl(sizeof(T), [](void* addr) { (T*)addr->~T(); });
        }

        virtual std::size_t getSizeUsed() const noexcept;
        std::size_t getSizeTotal() const noexcept;
        std::size_t getAreaId() const noexcept;

    protected:
        area_info(std::size_t areaId);

        virtual void constructImpl(const std::size_t sizeType,
                                   void (* constructor)(void *)) const;
        virtual void destructImpl(const std::size_t sizeType,
                                  void (* destructor)(void *)) const;

        std::size_t _areaId;
    };

    struct area_stack_info :
        public area_info
    {
        area_stack_info(std::size_t areaId);

        std::size_t getSizeUsed() const noexcept override final;

    protected:
        void constructImpl(const std::size_t sizeType,
                           void (* constructor)(void *)) const override final;
        void destructImpl(const std::size_t sizeType,
                          void (* destructor)(void *)) const override final;

        std::size_t _top = 0;
    };

    struct area_queue_info :
        public area_info
    {
        area_queue_info(std::size_t areaId);

        std::size_t getSizeUsed() const noexcept override final;
    
    protected:
        void constructImpl(const std::size_t sizeType,
                           void (* constructor)(void *)) const override final;
        void destructImpl(const std::size_t sizeType,
                          void (* destructor)(void *)) const override final;

        std::size_t _front = 0, _rear = 0;
    };
}
