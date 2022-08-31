#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

TEST(Array, swap_empty_array_do_nothing)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType a, b;
    ASSERT_EQ(a.data(), nullptr);
    ASSERT_EQ(a.count(), 0u);
    ASSERT_EQ(a.max_count(), 0u);
    ASSERT_EQ(a.allocator().allocation_count(), 0u);
    ASSERT_EQ(a.allocator().free_count(), 0u);
    ASSERT_EQ(b.data(), nullptr);
    ASSERT_EQ(b.count(), 0u);
    ASSERT_EQ(b.max_count(), 0u);
    ASSERT_EQ(b.allocator().allocation_count(), 0u);
    ASSERT_EQ(b.allocator().free_count(), 0u);

    a.swap(b);

    ASSERT_EQ(a.data(), nullptr);
    ASSERT_EQ(a.count(), 0u);
    ASSERT_EQ(a.max_count(), 0u);
    ASSERT_EQ(a.allocator().allocation_count(), 0u);
    ASSERT_EQ(a.allocator().free_count(), 0u);
    ASSERT_EQ(b.data(), nullptr);
    ASSERT_EQ(b.count(), 0u);
    ASSERT_EQ(b.max_count(), 0u);
    ASSERT_EQ(b.allocator().allocation_count(), 0u);
    ASSERT_EQ(b.allocator().free_count(), 0u);

    swap(a, b);

    ASSERT_EQ(a.data(), nullptr);
    ASSERT_EQ(a.count(), 0u);
    ASSERT_EQ(a.max_count(), 0u);
    ASSERT_EQ(a.allocator().allocation_count(), 0u);
    ASSERT_EQ(a.allocator().free_count(), 0u);
    ASSERT_EQ(b.data(), nullptr);
    ASSERT_EQ(b.count(), 0u);
    ASSERT_EQ(b.max_count(), 0u);
    ASSERT_EQ(b.allocator().allocation_count(), 0u);
    ASSERT_EQ(b.allocator().free_count(), 0u);
}

TEST(Array, swap_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    i32 a_destructor_called[2] = { false, false };
    ArrayType a;
    a.reserve(4);
    a.emplace_back(10, &a_destructor_called[0]);
    a.emplace_back(20, &a_destructor_called[1]);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 2u);
    ASSERT_EQ(a.max_count(), 4u);
    ASSERT_EQ(a[0].id(), 10);
    ASSERT_EQ(*a[0].destructor_counter(), 0);
    ASSERT_EQ(a[1].id(), 20);
    ASSERT_EQ(*a[1].destructor_counter(), 0);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    i32 b_destructor_called[3] = { false, false, false };
    ArrayType b;
    b.reserve(5);
    b.emplace_back(100, &b_destructor_called[0]);
    b.emplace_back(200, &b_destructor_called[1]);
    b.emplace_back(300, &b_destructor_called[1]);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 3u);
    ASSERT_EQ(b.max_count(), 5u);
    ASSERT_EQ(b[0].id(), 100);
    ASSERT_EQ(*b[0].destructor_counter(), 0);
    ASSERT_EQ(b[1].id(), 200);
    ASSERT_EQ(*b[1].destructor_counter(), 0);
    ASSERT_EQ(b[2].id(), 300);
    ASSERT_EQ(*b[2].destructor_counter(), 0);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);

    a.swap(b);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 3u);
    ASSERT_EQ(a.max_count(), 5u);
    ASSERT_EQ(a[0].id(), 100);
    ASSERT_EQ(*a[0].destructor_counter(), 0);
    ASSERT_EQ(a[1].id(), 200);
    ASSERT_EQ(*a[1].destructor_counter(), 0);
    ASSERT_EQ(a[2].id(), 300);
    ASSERT_EQ(*a[2].destructor_counter(), 0);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 2u);
    ASSERT_EQ(b.max_count(), 4u);
    ASSERT_EQ(b[0].id(), 10);
    ASSERT_EQ(*b[0].destructor_counter(), 0);
    ASSERT_EQ(b[1].id(), 20);
    ASSERT_EQ(*b[1].destructor_counter(), 0);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);


    swap(a, b);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 2u);
    ASSERT_EQ(a.max_count(), 4u);
    ASSERT_EQ(a[0].id(), 10);
    ASSERT_EQ(*a[0].destructor_counter(), 0);
    ASSERT_EQ(a[1].id(), 20);
    ASSERT_EQ(*a[1].destructor_counter(), 0);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 3u);
    ASSERT_EQ(b.max_count(), 5u);
    ASSERT_EQ(b[0].id(), 100);
    ASSERT_EQ(*b[0].destructor_counter(), 0);
    ASSERT_EQ(b[1].id(), 200);
    ASSERT_EQ(*b[1].destructor_counter(), 0);
    ASSERT_EQ(b[2].id(), 300);
    ASSERT_EQ(*b[2].destructor_counter(), 0);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);
}

TEST(Array, swap_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType a;
    a.reserve(4);
    a.emplace_back(10);
    a.emplace_back(20);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 2u);
    ASSERT_EQ(a.max_count(), 4u);
    ASSERT_EQ(a[0], 10u);
    ASSERT_EQ(a[1], 20u);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    ArrayType b;
    b.reserve(5);
    b.emplace_back(100);
    b.emplace_back(200);
    b.emplace_back(300);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 3u);
    ASSERT_EQ(b.max_count(), 5u);
    ASSERT_EQ(b[0], 100u);
    ASSERT_EQ(b[1], 200u);
    ASSERT_EQ(b[2], 300u);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);

    a.swap(b);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 3u);
    ASSERT_EQ(a.max_count(), 5u);
    ASSERT_EQ(a[0], 100u);
    ASSERT_EQ(a[1], 200u);
    ASSERT_EQ(a[2], 300u);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 2u);
    ASSERT_EQ(b.max_count(), 4u);
    ASSERT_EQ(b[0], 10u);
    ASSERT_EQ(b[1], 20u);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);


    swap(a, b);

    ASSERT_NE(a.data(), nullptr);
    ASSERT_EQ(a.count(), 2u);
    ASSERT_EQ(a.max_count(), 4u);
    ASSERT_EQ(a[0], 10u);
    ASSERT_EQ(a[1], 20u);
    ASSERT_EQ(a.allocator().allocation_count(), 1u);
    ASSERT_EQ(a.allocator().free_count(), 0u);

    ASSERT_NE(b.data(), nullptr);
    ASSERT_EQ(b.count(), 3u);
    ASSERT_EQ(b.max_count(), 5u);
    ASSERT_EQ(b[0], 100u);
    ASSERT_EQ(b[1], 200u);
    ASSERT_EQ(b[2], 300u);
    ASSERT_EQ(b.allocator().allocation_count(), 1u);
    ASSERT_EQ(b.allocator().free_count(), 0u);
}