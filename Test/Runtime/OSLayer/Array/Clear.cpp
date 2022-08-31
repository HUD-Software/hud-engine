#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

TEST(Array, clear_destroy_but_keep_allocated_memory_with_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    i32 destructor_called[2] = { false, false };
    ArrayType array;
    array.reserve(2);
    const Type* const buffer = array.data();
    array.emplace_back(10, &destructor_called[0]);
    array.emplace_back(20, &destructor_called[1]);

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.count(), 2u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array[0].id(), 10);
    ASSERT_EQ(*array[0].destructor_counter(), 0);
    ASSERT_EQ(array[1].id(), 20);
    ASSERT_EQ(*array[1].destructor_counter(), 0);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear();

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.data(), buffer);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
    ASSERT_TRUE(destructor_called[0]);
    ASSERT_TRUE(destructor_called[1]);
}

TEST(Array, clear_destroy_but_keep_allocated_memory_with_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    array.reserve(2);
    const Type* const buffer = array.data();
    array.emplace_back(10);
    array.emplace_back(20);

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.count(), 2u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array[0], Type(10));
    ASSERT_EQ(array[1], Type(20));
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear();

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.data(), buffer);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
}

TEST(Array, clear_empty_do_nothing_with_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear();
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
}

TEST(Array, clear_empty_do_nothing_with_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear();
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
}

TEST(Array, clear_shrink_destroy_but_keep_allocated_memory_with_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    i32 destructor_called[2] = { false, false };
    ArrayType array;
    array.reserve(2);
    array.emplace_back(10, &destructor_called[0]);
    array.emplace_back(20, &destructor_called[1]);

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.count(), 2u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array[0].id(), 10);
    ASSERT_EQ(*array[1].destructor_counter(), 0);
    ASSERT_EQ(array[1].id(), 20);
    ASSERT_EQ(*array[1].destructor_counter(), 0);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear_shrink();

    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 1u);
    ASSERT_TRUE(destructor_called[0]);
    ASSERT_TRUE(destructor_called[1]);
}

TEST(Array, clear_shrink_destroy_but_keep_allocated_memory_with_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    array.reserve(2);
    array.emplace_back(10);
    array.emplace_back(20);

    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.count(), 2u);
    ASSERT_EQ(array.max_count(), 2u);
    ASSERT_EQ(array[0], Type(10));
    ASSERT_EQ(array[1], Type(20));
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear_shrink();

    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 1u);
}

TEST(Array, clear_shrink_empty_do_nothing_with_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear_shrink();
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
}

TEST(Array, clear_shrink_empty_do_nothing_with_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    array.clear_shrink();
    ASSERT_EQ(array.data(), nullptr);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 0u);
    ASSERT_EQ(array.allocator().allocation_count(), 0u);
    ASSERT_EQ(array.allocator().free_count(), 0u);
}