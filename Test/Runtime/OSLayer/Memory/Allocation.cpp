
#include <OSLayer/Memory.h>
#include "Misc/LeakGuard.h"

TEST(Memory, allocate)
{
    using namespace hud;

    // Non constant
    {

        // Allocation should success and allocate a u32 on the heap
        constexpr usize allocation_size = sizeof(u32) * 2;
        void* ptr = Memory::allocate(allocation_size);
        HUD_TEST::LeakGuard leak_guard(ptr);
        ASSERT_NE(ptr, nullptr);

        // Allocation should failed (usize_max is too big)  and allocate should return nullptr
        void* ptr_2 = Memory::allocate(usize_max);
        HUD_TEST::LeakGuard leak_guard_2(ptr_2);
        ASSERT_EQ(ptr_2, nullptr);
    }

}

TEST(Memory, allocate_and_free_are_usable_in_constexpr)
{
    using namespace hud;

    constexpr bool allocate_const = []() -> bool {
        i32* const_ptr = Memory::allocate_array<i32>(2);
        bool allocated = const_ptr != nullptr;
        Memory::free_array(const_ptr, 2);
        return allocated;
    }();
    ASSERT_TRUE(allocate_const);
}

TEST(Memory, allocate_zero)
{
    using namespace hud;

    // Allocation should success and allocate a 2*u32 on the heap and fill it with 0
    constexpr usize allocation_size = sizeof(u32) * 2;
    void* ptr = Memory::allocate_zero(allocation_size);
    HUD_TEST::LeakGuard leak_guard(ptr);
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(*static_cast<u32*>(ptr), 0u);
    ASSERT_EQ(*(static_cast<u32*>(ptr) + 1), 0u);

    // Allocation should failed (usize_max is too big)  and allocate should return nullptr
    void* ptr_2 = Memory::allocate_zero(usize_max);
    HUD_TEST::LeakGuard leak_guard_2(ptr_2);
    ASSERT_EQ(ptr_2, nullptr);
}

TEST(Memory, allocate_align)
{
    using namespace hud;

    for (u32 aligment = 1; aligment <= 256; aligment <<= 1) {

        // Allocation should success and allocate a u32 on the heap
        void* ptr = Memory::allocate_align(sizeof(u32) * 2, aligment);
        HUD_TEST::AlignLeakGuard leak_guard(ptr);
        ASSERT_NE(ptr, nullptr);
        ASSERT_TRUE(Memory::is_pointer_aligned(ptr, aligment));

        // Allocation should failed (usize_max is too big)  and allocate should return nullptr
        void* ptr_2 = Memory::allocate_align(usize_max - (Memory::ALIGNED_MALLOC_HEADER_SIZE + aligment), aligment);
        HUD_TEST::AlignLeakGuard leak_guard_2(ptr_2);
        ASSERT_EQ(ptr_2, nullptr);
    }
}

TEST(Memory, allocate_align_zero)
{
    using namespace hud;

    for (u32 aligment = 1; aligment <= 256; aligment <<= 1) {

        // Allocation should success and allocate a u32 on the heap
        void* ptr = Memory::allocate_align_zero(sizeof(u32) * 2, aligment);
        HUD_TEST::AlignLeakGuard leak_guard(ptr);
        ASSERT_NE(ptr, nullptr);
        ASSERT_TRUE(Memory::is_pointer_aligned(ptr, aligment));
        ASSERT_EQ(*static_cast<u32*>(ptr), 0u);
        ASSERT_EQ(*(static_cast<u32*>(ptr) + 1), 0u);

        // Allocation should failed (usize_max is too big)  and allocate should return nullptr
        void* ptr_2 = Memory::allocate_align_zero(usize_max - (Memory::ALIGNED_MALLOC_HEADER_SIZE + aligment), aligment);
        HUD_TEST::AlignLeakGuard leak_guard_2(ptr_2);
        ASSERT_EQ(ptr_2, nullptr);
    }
}

TEST(Memory, free)
{
    using namespace hud;

    // Difficult to test, at least it should not crash
    Memory::free(Memory::allocate(sizeof(u32)));

    // Do nothing without crashing
    Memory::free(nullptr);
}


TEST(Memory, free_align)
{
    using namespace hud;

    // Difficult to test, at least it should not crash
    Memory::free_align(Memory::allocate_align(sizeof(u32), 128));

    // Do nothing without crashing
    Memory::free_align(nullptr);
}

TEST(Memory, allocate_align_and_free_align_are_usable_in_consteval)
{
    using namespace hud;

    constexpr bool allocate_const = []() -> bool {
        i32* const_ptr = Memory::allocate_align<i32>(2, 128);
        bool allocated = const_ptr != nullptr;
        Memory::free_align(const_ptr, 2);
        return allocated;
    }();
    ASSERT_TRUE(allocate_const);
}

TEST(Memory, reallocate)
{
    using namespace hud;

    u32* ptr = reinterpret_cast<u32*>(Memory::reallocate(nullptr, sizeof(u32)));
    HUD_TEST::LeakGuard guard(ptr);
    ASSERT_NE(ptr, nullptr);
    *ptr = 2;
    ptr = reinterpret_cast<u32*>(Memory::reallocate(ptr, sizeof(u32) * 2));
    ASSERT_NE(ptr, nullptr);
    *(ptr + 1) = 3;
    ASSERT_EQ(*ptr, 2u);
    ASSERT_EQ(*(ptr + 1), 3u  );
    ASSERT_EQ(Memory::reallocate(ptr, 0), nullptr);

    //Do not free, it's already free
    guard.leak();
}

TEST(Memory, reallocate_align)
{
    using namespace hud;

    struct A {
        A(A&& other) = default;
        u32 i;
    };
    for (u32 aligment = 1; aligment <= 256; aligment <<= 1) {

        A* ptr = reinterpret_cast<A*>(Memory::reallocate_align(nullptr, sizeof(A), aligment));
        HUD_TEST::AlignLeakGuard guard(ptr);
        ASSERT_NE(ptr, nullptr);
        ASSERT_TRUE(Memory::is_pointer_aligned(ptr, aligment));
        ptr->i = 2;
        ptr = reinterpret_cast<A*>(Memory::reallocate_align(ptr, sizeof(A) * 2, aligment));
        ASSERT_NE(ptr, nullptr);
        ASSERT_TRUE(Memory::is_pointer_aligned(ptr, aligment));
        (ptr + 1)->i = 3;
        ASSERT_EQ(ptr->i, 2u);
        ASSERT_EQ((ptr + 1)->i, 3u);
        ASSERT_EQ(Memory::reallocate_align(ptr, 0, 4), nullptr);
        guard.leak();
    }
}