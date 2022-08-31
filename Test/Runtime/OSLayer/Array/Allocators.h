#pragma once
#ifndef HD_INC_TEST_ARRAY_ALLOCATORS_H
#define HD_INC_TEST_ARRAY_ALLOCATORS_H
#include <OSLayer/Allocators/AlignedHeapAllocator.h>

HUD_TEST_NAMESPACE{
    template<u32 alignement>
    struct ArrayAllocator
    {
        using AllocatorType = AlignedHeapAllocator<alignement>;

        template<typename T>
        using AllocationType = Allocation<T>;
        
    public:
        /** Default constructor. */
        constexpr ArrayAllocator() noexcept = default;

        /** Construct allocator with a unique id. */
        constexpr ArrayAllocator(u32 id) noexcept
            : unique_id(id) {
        }

        /** Copy constructor. */
        constexpr ArrayAllocator(const ArrayAllocator& other) noexcept = default;

        /** Move construct the array allocator. */
        constexpr ArrayAllocator(ArrayAllocator&&) noexcept
            : count_of_move_construct(1) {
            // Ignore the move of informations,
            // Just increment counter for tests
        }

        /** Move assign the array allocator. */
        constexpr ArrayAllocator& operator=(ArrayAllocator&&) noexcept {
            // Ignore the move of informations
            // Just increment counter for tests
            count_of_move_assign++;
            return *this;
        }

        /** Copy assign the array allocator. */
        constexpr ArrayAllocator& operator=(const ArrayAllocator&) noexcept = default;

        /**
        * Allocate memory block
        * @tparam T The element type to allocate
        * @param count Number of element T to allocate
        * @return Allocation of the allocated aligned memory block, empty Allocation if failed
        */
        template<typename T = u8>
        [[nodiscard]]
        constexpr AllocationType<T> allocate(const usize count) noexcept {
            auto buffer = allocator.template allocate<T>(count);
            if (!buffer.is_empty()) {
                count_of_alloc++;
            }
            return buffer;
        }

        /**
        * Free memory block
        * @param slice The slice to free
        */
        template<typename T = u8>
        constexpr void free(AllocationType<T>& buffer) noexcept {
            if (!buffer.is_empty()) {
                count_of_free++;
            }
            allocator.free(buffer);
        }

        /** Retrieves count of allocation done. */
        constexpr u32 allocation_count() const noexcept {
            return count_of_alloc;
        }

        /** Retrieves count of free done. */
        constexpr u32 free_count() const noexcept {
            return count_of_free;
        }

        /** Retrieves count of move assignement done. */
        constexpr u32 move_assign_count() const noexcept {
            return count_of_move_assign;
        }

        /** Retrieves count of move construction done. */
        constexpr u32 move_construct_count() const noexcept {
            return count_of_move_construct;
        }

        /** Retrieves id the the allocator. */
        constexpr u32 id() const noexcept {
            return unique_id;
        }

    private:
        AllocatorType allocator;
        u32 count_of_alloc = 0u;
        u32 count_of_free = 0u;
        u32 count_of_move_assign = 0u;
        u32 count_of_move_construct = 0u;
        u32 unique_id = 0;
    };

    template<u32 alignement>
    struct ArrayAllocator2 : public ArrayAllocator<alignement>
    { };

   

} // HUD_TEST_NAMESPACE

#endif // HD_INC_TEST_ARRAY_ALLOCATORS_H
