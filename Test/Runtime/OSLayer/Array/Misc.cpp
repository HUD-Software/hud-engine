#include <OSLayer/Containers/Array.h>

#include "Array/Allocators.h"


TEST(Array, less_or_equal_size_as_std_vector)
{
    ASSERT_LE(sizeof(hud::Array<i32>), sizeof(std::vector<i32>));
}

TEST(Array, count_return_count_of_element)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Count return 0 if array is empty
    {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);
    }

    // Count return number of element if not empty
    {
        ArrayType array({ 1, 2 });
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 2u);
        ASSERT_EQ(array.max_count(), 2u);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);
    }
}

TEST(Array, byte_count_return_count_of_bytes_of_all_elements) {
    using Type = usize;
    using ArrayType = hud::Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Count return 0 if array is empty
    {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.byte_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);
    }

    // Count return number of element if not empty
    {
        ArrayType array({ 1, 2 });
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 2u);
        ASSERT_EQ(array.byte_count(), 2u * sizeof(Type));
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);
    }
}

TEST(Array, max_count_return_allocated_count_of_element) 
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Max_count return 0 if array is empty
    {
        ArrayType array;

        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), array.max_count());
        ASSERT_EQ(array.max_count(), 0u);
    }

    //Max_count return maximum number of element allocated
    {
        ArrayType array;
        array.reserve(4);
        array.emplace_back(10);
        array.emplace_back(20);

        ASSERT_NE(array.data(), nullptr);
        ASSERT_NE(array.count(), array.max_count());
        ASSERT_EQ(array.max_count(), 4u);
    }
}

TEST(Array, max_byte_count_return_count_of_bytes_of_all_elements) {
    using Type = usize;
    using ArrayType = hud::Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Max_count return 0 if array is empty
    {
        ArrayType array;

        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.byte_count(), array.max_byte_count());
        ASSERT_EQ(array.max_byte_count(), 0u);
    }

    //Max_count return maximum number of element allocated
    {
        ArrayType array;
        array.reserve(4);
        array.emplace_back(10);
        array.emplace_back(20);

        ASSERT_NE(array.data(), nullptr);
        ASSERT_NE(array.byte_count(), array.max_byte_count());
        ASSERT_EQ(array.max_byte_count(), 4u*sizeof(Type));
    }
}

TEST(Array, allocator_return_the_allocator)
{
    using namespace hud;
    using Type = usize;
    using AllocatorType = HUD_TEST::ArrayAllocator<alignof(Type)>;
    using ArrayType = Array<Type, AllocatorType>;

    // Check that the default id is not the one we use to test if the allocator is really the one given to the constructor
    const u32 id = 42;
    ASSERT_NE(AllocatorType().id(), id);

    AllocatorType allocator(42);
    ArrayType array({ 10,20 }, allocator);
    ASSERT_EQ(array.allocator().id(), allocator.id());
}

TEST(Array, data_return_nullptr_if_array_is_empty) 
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.data(), nullptr);
}

TEST(Array, data_return_pointer_to_the_first_element_if_array_is_not_empty)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array({ 1,2 });
    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(*array.data(), 1u);
}


TEST(Array, slack_return_zero_if_array_is_empty) 
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_EQ(array.slack(), 0u);
}

TEST(Array, slack_return_zero_if_count_equal_max_count_of_non_empty_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array({ 1,2 });
    ASSERT_FALSE(array.is_empty());
    ASSERT_EQ(array.count(), array.max_count());
    ASSERT_EQ(array.slack(), 0u);
}

TEST(Array, slack_return_extra_element_allocated_memory_of_non_empty_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array({ 1,2 });
    array.reserve(4);
    ASSERT_FALSE(array.is_empty());
    ASSERT_NE(array.count(), array.max_count());
    ASSERT_EQ(array.slack(), 2u);
}

TEST(Array, is_valid_index_retur_false_for_empty_array)
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

    ASSERT_FALSE(array.is_valid_index(0));
    ASSERT_FALSE(array.is_valid_index(1));

}

TEST(Array, is_valid_index_check_if_an_index_can_be_used_to_acces_an_element)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array({ 1,2 }, 2);
    ASSERT_NE(array.data(), nullptr);
    ASSERT_EQ(array.count(), 2u);
    ASSERT_EQ(array.max_count(), 4u);
    ASSERT_EQ(array.allocator().allocation_count(), 1u);
    ASSERT_EQ(array.allocator().free_count(), 0u);

    ASSERT_TRUE(array.is_valid_index(0));
    ASSERT_TRUE(array.is_valid_index(1));
    ASSERT_FALSE(array.is_valid_index(2));
    ASSERT_FALSE(array.is_valid_index(3));
    ASSERT_FALSE(array.is_valid_index(4));

}

TEST(Array, is_empty_return_if_array_contains_elements_or_not)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;
    ASSERT_TRUE(array.is_empty());

    array.reserve(4);
    ASSERT_EQ(array.count(), 0u);
    ASSERT_EQ(array.max_count(), 4u);
    ASSERT_TRUE(array.is_empty());

    array.emplace_back(10);
    ASSERT_EQ(array.count(), 1u);
    ASSERT_EQ(array.max_count(), 4u);
    ASSERT_FALSE(array.is_empty());
}

TEST(Array, operator_indexed_accessor_return_the_element_at_the_given_index)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10,20 }, 4);
        ASSERT_EQ(array[0], 10u);
        ASSERT_EQ(array[1], 20u);
    }

    // const array
    {
        const ArrayType array({ 10,20 }, 4);
        ASSERT_EQ(array[0], 10u);
        ASSERT_EQ(array[1], 20u);
    }
}

TEST(Array, sub_slice_return_a_slice_on_elements_in_the_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10, 20, 30, 40, 50 }, 4);
        Slice<Type> slice = array.sub_slice(0, 5);
        ASSERT_EQ(slice.count(), array.count());
        ASSERT_EQ(slice.data(), array.data());
    }

    // const array
    {
        const ArrayType array({ 10, 20, 30, 40, 50 }, 4);
        const Slice<Type> slice = array.sub_slice(0, 5);
        ASSERT_EQ(slice.count(), array.count());
        ASSERT_EQ(slice.data(), array.data());
    }
}

TEST(Array, first_return_the_first_element_in_the_array) 
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.first(), 10u);
    }

    // const array
    {
        const ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.first(), 10u);
    }
}

TEST(Array, first_return_the_first_nth_element_in_the_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.first(1), 20u);
    }

    // const array
    {
        const ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.first(1), 20u);
    }
}

TEST(Array, last_return_the_last_element_in_the_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.last(), 30u);
    }

    // const array
    {
        const ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.last(), 30u);
    }
}

TEST(Array, last_return_the_last_nth_element_in_the_array)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    // Non const array
    {
        ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.last(1), 20u);
    }

    // const array
    {
        const ArrayType array({ 10,20,30 }, 4);
        ASSERT_EQ(array.last(1), 20u);
    }
}