#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

#include <OSLayer/Memory.h> // Memory::default_construct
TEST(Array, add_no_construct_do_not_call_constructor)
{
    using namespace hud;
    using Type = HUD_TEST::NonDefaultConstructibleType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(!IsConstructibleV<Type>);

    // test with reallocation
    {
        const auto test = []() {
            ArrayType array;

            // Insert one element without constructing it
            const usize index_0 = array.add_no_construct(2);
            const auto result_0 = std::tuple{
                index_0,
                array.data() != nullptr,
                array.count(),
                array.max_count(),
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };

            // Construct only in constant_evaluated
            // Constant evaluation do not allowed to access non initialized memory
            if (hud::is_constant_evaluated()) {
                Memory::construct_array_at(array.data(), array.data()+2, i32_max);
            }

            // Insert one element without constructing it
            const usize index_1 = array.add_no_construct(3);
            const auto result_1 = std::tuple{
                index_1,
                array.data() != nullptr,
                array.count(),
                array.max_count(),
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };

            return std::tuple{
                result_0,
                result_1
            };
        };

        // Non constant
        {
            const auto result = test();
            const auto result_0 = std::get<0>(result);
            ASSERT_EQ(std::get<0>(result_0), 0u);
            ASSERT_TRUE(std::get<1>(result_0));
            ASSERT_EQ(std::get<2>(result_0), 2u);
            ASSERT_EQ(std::get<3>(result_0), 2u);
            ASSERT_EQ(std::get<4>(result_0), 1u);
            ASSERT_EQ(std::get<5>(result_0), 0u);

            const auto result_1 = std::get<1>(result);
            ASSERT_EQ(std::get<0>(result_1), 2u);
            ASSERT_TRUE(std::get<1>(result_1));
            ASSERT_EQ(std::get<2>(result_1), 5u);
            ASSERT_EQ(std::get<3>(result_1), 5u);
            ASSERT_EQ(std::get<4>(result_1), 2u);
            ASSERT_EQ(std::get<5>(result_1), 1u);
        }

        // Constant
        {
            constexpr auto result = test();
            const auto result_0 = std::get<0>(result);
            ASSERT_EQ(std::get<0>(result_0), 0u);
            ASSERT_TRUE(std::get<1>(result_0));
            ASSERT_EQ(std::get<2>(result_0), 2u);
            ASSERT_EQ(std::get<3>(result_0), 2u);
            ASSERT_EQ(std::get<4>(result_0), 1u);
            ASSERT_EQ(std::get<5>(result_0), 0u);

            const auto result_1 = std::get<1>(result);
            ASSERT_EQ(std::get<0>(result_1), 2u);
            ASSERT_TRUE(std::get<1>(result_1));
            ASSERT_EQ(std::get<2>(result_1), 5u);
            ASSERT_EQ(std::get<3>(result_1), 5u);
            ASSERT_EQ(std::get<4>(result_1), 2u);
            ASSERT_EQ(std::get<5>(result_1), 1u);
        }
    }


    // test without reallocation
    {
        const auto test = []() {
            ArrayType array;
            array.reserve(5);

            // Insert one element without constructing it
            const usize index_0 = array.add_no_construct(2);
            const auto result_0 = std::tuple{
                index_0,
                array.data() != nullptr,
                array.count(),
                array.max_count(),
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };

            // Construct only in constant_evaluated
            // Constant evaluation do not allowed to access non initialized memory
            if (hud::is_constant_evaluated()) {
                Memory::construct_array_at(array.data(), array.data() + 2, i32_max);
            }

            // Insert one element without constructing it
            const usize index_1 = array.add_no_construct(3);
            const auto result_1 = std::tuple{
                index_1,
                array.data() != nullptr,
                array.count(),
                array.max_count(),
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };

            return std::tuple{
                result_0,
                result_1
            };
        };

        // Non constant
        {
            const auto result = test();
            const auto result_0 = std::get<0>(result);
            ASSERT_EQ(std::get<0>(result_0), 0u);
            ASSERT_TRUE(std::get<1>(result_0));
            ASSERT_EQ(std::get<2>(result_0), 2u);
            ASSERT_EQ(std::get<3>(result_0), 5u);
            ASSERT_EQ(std::get<4>(result_0), 1u);
            ASSERT_EQ(std::get<5>(result_0), 0u);

            const auto result_1 = std::get<1>(result);
            ASSERT_EQ(std::get<0>(result_1), 2u);
            ASSERT_TRUE(std::get<1>(result_1));
            ASSERT_EQ(std::get<2>(result_1), 5u);
            ASSERT_EQ(std::get<3>(result_1), 5u);
            ASSERT_EQ(std::get<4>(result_1), 1u);
            ASSERT_EQ(std::get<5>(result_1), 0u);
        }

        // Constant
        {
            constexpr auto result = test();
            const auto result_0 = std::get<0>(result);
            ASSERT_EQ(std::get<0>(result_0), 0u);
            ASSERT_TRUE(std::get<1>(result_0));
            ASSERT_EQ(std::get<2>(result_0), 2u);
            ASSERT_EQ(std::get<3>(result_0), 5u);
            ASSERT_EQ(std::get<4>(result_0), 1u);
            ASSERT_EQ(std::get<5>(result_0), 0u);

            const auto result_1 = std::get<1>(result);
            ASSERT_EQ(std::get<0>(result_1), 2u);
            ASSERT_TRUE(std::get<1>(result_1));
            ASSERT_EQ(std::get<2>(result_1), 5u);
            ASSERT_EQ(std::get<3>(result_1), 5u);
            ASSERT_EQ(std::get<4>(result_1), 1u);
            ASSERT_EQ(std::get<5>(result_1), 0u);
        }
    }
}