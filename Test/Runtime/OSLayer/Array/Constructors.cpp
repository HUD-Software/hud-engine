#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

TEST(Array, default_constructor_should_allocate_no_memory)
{
    auto test = []() -> std::tuple<bool, usize, usize> {
        hud::Array<hud::u32> array;
        return { array.data() == nullptr, array.count(), array.max_count() };
    };

    // Non Constant
    {
        auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
    }
}

TEST(Array, construct_by_copying_raw_data_array_of_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    using TypeList = std::tuple<i8, i16, i32, i64, u8, u16, u32, u64, uptr, iptr, usize, isize>;

    HUD_TEST::for_each_type<TypeList>()([]<typename T>() noexcept {

        static_assert(IsBitwiseCopyConstructibleV<T>);


        // test with default allocator no extra
        {
            auto test_default_allocator = [](const T* raw, usize element_count) {
                Array<T> array(raw, element_count);
                bool all_values_copied = true;

                // Ensure values are correclty copied
                for (usize index = 0; index < element_count; index++) {
                    if (*(array.data() + index) != raw[index]) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Allocation of 4 i32 should be done
                    array.data() != nullptr,
                    array.count(),
                    array.max_count(),

                    // Ensure it's not the same memory buffer
                    array.data() != &raw[0],

                    // Ensure values are correclty copied
                    all_values_copied
                };
            };

            // Non Constant
            {
                constexpr usize element_count = 4;
                constexpr T raw[element_count] = { 1,2,3,4 };
                const auto result = test_default_allocator(raw, element_count);
                // Allocation of 4 i32 should be done
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), element_count);
                ASSERT_EQ(std::get<2>(result), element_count);

                // Ensure it's not the same memory buffer
                ASSERT_TRUE(std::get<3>(result));

                // Ensure values are correclty copied
                ASSERT_TRUE(std::get<4>(result));
            }

            // Constant
            {
                constexpr usize element_count = 4;
                constexpr T raw[element_count] = { 1,2,3,4 };
                constexpr auto result = test_default_allocator(raw, element_count);
                // Allocation of 4 i32 should be done
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), element_count);
                ASSERT_EQ(std::get<2>(result), element_count);

                // Ensure it's not the same memory buffer
                ASSERT_TRUE(std::get<3>(result));

                // Ensure values are correclty copied
                ASSERT_TRUE(std::get<4>(result));
            }
        }

        // test with allocator no extra
        {
            auto test_with_allocator = [](const T* raw, usize element_count) {
                Array<T, HUD_TEST::ArrayAllocator<alignof(T)>> array(raw, element_count, HUD_TEST::ArrayAllocator<alignof(T)>{});
                bool all_values_copied = true;

                // Ensure values are correclty copied
                for (usize index = 0; index < element_count; index++) {
                    if (*(array.data() + index) != raw[index]) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Allocation of 4 i32 should be done
                    array.data() != nullptr,
                    array.count(),
                    array.max_count(),

                    // Ensure it's not the same memory buffer
                    array.data() != &raw[0],

                    // Ensure values are correclty copied
                    all_values_copied,

                    // Ensure we are allocating only one time
                    array.allocator().allocation_count(),
                    array.allocator().free_count()
                };
            };

            // Non Constant
            {
                constexpr usize element_count = 4;
                constexpr T raw[element_count] = { 1,2,3,4 };
                const auto result = test_with_allocator(raw, element_count);
                // Allocation of 4 i32 should be done
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), element_count);
                ASSERT_EQ(std::get<2>(result), element_count);

                // Ensure it's not the same memory buffer
                ASSERT_TRUE(std::get<3>(result));

                // Ensure values are correclty copied
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr usize element_count = 4;
                constexpr T raw[element_count] = { 1,2,3,4 };
                constexpr auto result = test_with_allocator(raw, element_count);
                // Allocation of 4 i32 should be done
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), element_count);
                ASSERT_EQ(std::get<2>(result), element_count);

                // Ensure it's not the same memory buffer
                ASSERT_TRUE(std::get<3>(result));

                // Ensure values are correclty copied
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator with extra
                    {
                        auto test_default_allocator = [](const T* raw, usize element_count) {
                            Array<T> array(raw, element_count, extra);
                            bool all_values_copied = true;

                            // Ensure values are correclty copied
                            for (usize index = 0; index < element_count; index++) {
                                if (*(array.data() + index) != raw[index]) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Allocation of 4 i32 should be done
                                array.data() != nullptr,
                                array.count(),
                                array.max_count(),

                                // Ensure it's not the same memory buffer
                                array.data() != &raw[0],

                                // Ensure values are correclty copied
                                all_values_copied
                            };

                        };
                        // Non Constant
                        {
                            constexpr usize element_count = 4;
                            constexpr T raw[element_count] = { 1,2,3,4 };
                            const auto result = test_default_allocator(raw, element_count);
                            // Allocation of 4 i32 should be done
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), element_count);
                            ASSERT_EQ(std::get<2>(result), element_count + extra);

                            // Ensure it's not the same memory buffer
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure values are correclty copied
                            ASSERT_TRUE(std::get<4>(result));
                        }

                        // Constant
                        {
                            constexpr usize element_count = 4;
                            constexpr T raw[element_count] = { 1,2,3,4 };
                            constexpr auto result = test_default_allocator(raw, element_count);
                            // Allocation of 4 i32 should be done
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), element_count);
                            ASSERT_EQ(std::get<2>(result), element_count + extra);

                            // Ensure it's not the same memory buffer
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure values are correclty copied
                            ASSERT_TRUE(std::get<4>(result));
                        }

                    }

                    // Test with allocator with extra
                    {
                        auto test_with_allocator = [](const T* raw, usize element_count) {
                            Array<T, HUD_TEST::ArrayAllocator<alignof(T)>> array(raw, element_count, extra, HUD_TEST::ArrayAllocator<alignof(T)>{});
                            bool all_values_copied = true;

                            // Ensure values are correclty copied
                            for (usize index = 0; index < element_count; index++) {
                                if (*(array.data() + index) != raw[index]) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Allocation of 4 i32 should be done
                                array.data() != nullptr,
                                array.count(),
                                array.max_count(),

                                // Ensure it's not the same memory buffer
                                array.data() != &raw[0],

                                // Ensure values are correclty copied
                                all_values_copied,

                                // Ensure we are allocating only one time
                                array.allocator().allocation_count(),
                                array.allocator().free_count()
                            };
                        };

                        // Non Constant
                        {
                            constexpr usize element_count = 4;
                            constexpr T raw[element_count] = { 1,2,3,4 };
                            const auto result = test_with_allocator(raw, element_count);
                            // Allocation of 4 i32 should be done
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), element_count);
                            ASSERT_EQ(std::get<2>(result), element_count + extra);

                            // Ensure it's not the same memory buffer
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure values are correclty copied
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr usize element_count = 4;
                            constexpr T raw[element_count] = { 1,2,3,4 };
                            constexpr auto result = test_with_allocator(raw, element_count);

                            // Allocation of 4 i32 should be done
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), element_count);
                            ASSERT_EQ(std::get<2>(result), element_count + extra);

                            // Ensure it's not the same memory buffer
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure values are correclty copied
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, construct_by_copying_raw_data_array_of_non_bitwise_copy_constructible_same_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    // test with default allocator no extra
    {
        auto test_default_allocator = [](const Type* raw, usize element_count) {
            Array<Type> array(raw, element_count);

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < element_count; index++) {
                if (array[index].id() != raw[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < element_count; index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != raw[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                array.data() != &raw[0],

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called

            };
        };

        // Non Constant
        {
            constexpr usize element_count = 4;
            constexpr Type raw[element_count] = { 1,2,3,4 };
            const auto result = test_default_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }

        // Constant
        {
            constexpr usize element_count = 4;
            constexpr Type raw[element_count] = { 1,2,3,4 };
            constexpr auto result = test_default_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](const Type* raw, usize element_count) {
            Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(raw, element_count, HUD_TEST::ArrayAllocator<alignof(Type)>{});

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < element_count; index++) {
                if (array[index].id() != raw[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < element_count; index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != raw[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }
            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                array.data() != &raw[0],

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()

            };
        };

        // Non Constant
        {
            constexpr usize element_count = 4;
            constexpr Type raw[element_count] = { 1,2,3,4 };
            const auto result = test_with_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }

        // Constant
        {
            constexpr usize element_count = 4;
            constexpr Type raw[element_count] = { 1,2,3,4 };
            constexpr auto result = test_with_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allcoator with extra
                {
                    auto test_default_allocator = [](const Type* raw, usize element_count) {
                        Array<Type> array(raw, element_count, extra);

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < element_count; index++) {
                            if (array[index].id() != raw[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < element_count; index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != raw[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != &raw[0],

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called

                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type raw[element_count] = { 1,2,3,4 };
                        const auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }
                }


                // Test with allocator with extra
                {
                    auto test_with_allocator = [](const Type* raw, usize element_count) {
                        Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(raw, element_count, extra, HUD_TEST::ArrayAllocator<alignof(Type)>{});

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < element_count; index++) {
                            if (array[index].id() != raw[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < element_count; index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != raw[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }
                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != &raw[0],

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()

                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type raw[element_count] = { 1,2,3,4 };
                        const auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, construct_by_copying_raw_data_array_of_bitwise_copy_constructible_different_type)
{
    using namespace hud;

    using TypesToTest = std::tuple<i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, uptr, iptr, usize, isize>;

    bool at_least_one_copy_tested = false;
    HUD_TEST::for_each_type<TypesToTest>()([&at_least_one_copy_tested]<typename T>() noexcept {
        HUD_TEST::for_each_type<TypesToTest>()([&at_least_one_copy_tested]<typename U>() noexcept {

            // Test only types that are not the same but are bitwise copy constructible
            if constexpr (!std::is_same_v<T, U> && IsBitwiseCopyConstructibleV<T, U>)
            {
                at_least_one_copy_tested = true;

                //test with default allocator no extra
                {
                    auto test_default_allocator = [](const U* raw, usize element_count) {
                        Array<T> array(raw, element_count);
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < element_count; index++) {
                            if (*(array.data() + index) != static_cast<T>(raw[index])) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)&raw[0],

                            // Ensure values are correclty copied
                            all_values_copied
                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr U raw[element_count] = { 1,2,3,4 };
                        const auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr U raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }
                }

                // test with allocator no extra
                {
                    auto test_with_allocator = [](const U* raw, usize element_count) {
                        Array<T, HUD_TEST::ArrayAllocator<alignof(T)>> array(raw, element_count, HUD_TEST::ArrayAllocator<alignof(T)>{});
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < element_count; index++) {
                            if (*(array.data() + index) != static_cast<T>(raw[index])) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)&raw[0],

                            // Ensure values are correclty copied
                            all_values_copied,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()
                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr U raw[element_count] = { 1,2,3,4 };
                        const auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr U raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }
                }

                {
                    HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                        []<usize extra>() {

                        // Test default allocator with extra
                            {
                                auto test_default_allocator = [](const U* raw, usize element_count) {
                                    Array<T> array(raw, element_count, extra);
                                    bool all_values_copied = true;

                                    // Ensure values are correclty copied
                                    for (usize index = 0; index < element_count; index++) {
                                        if (*(array.data() + index) != static_cast<T>(raw[index])) {
                                            all_values_copied = false;
                                            break;
                                        }
                                    }

                                    return std::tuple{
                                        // Allocation of 4 i32 should be done
                                        array.data() != nullptr,
                                        array.count(),
                                        array.max_count(),

                                        // Ensure it's not the same memory buffer
                                        (void*)array.data() != (void*)&raw[0],

                                        // Ensure values are correclty copied
                                        all_values_copied
                                    };

                                };
                                // Non Constant
                                {
                                    constexpr usize element_count = 4;
                                    constexpr U raw[element_count] = { 1,2,3,4 };
                                    const auto result = test_default_allocator(raw, element_count);
                                    // Allocation of 4 i32 should be done
                                    ASSERT_TRUE(std::get<0>(result));
                                    ASSERT_EQ(std::get<1>(result), element_count);
                                    ASSERT_EQ(std::get<2>(result), element_count + extra);

                                    // Ensure it's not the same memory buffer
                                    ASSERT_TRUE(std::get<3>(result));

                                    // Ensure values are correclty copied
                                    ASSERT_TRUE(std::get<4>(result));
                                }

                                // Constant
                                {
                                    constexpr usize element_count = 4;
                                    constexpr U raw[element_count] = { 1,2,3,4 };
                                    constexpr auto result = test_default_allocator(raw, element_count);
                                    // Allocation of 4 i32 should be done
                                    ASSERT_TRUE(std::get<0>(result));
                                    ASSERT_EQ(std::get<1>(result), element_count);
                                    ASSERT_EQ(std::get<2>(result), element_count + extra);

                                    // Ensure it's not the same memory buffer
                                    ASSERT_TRUE(std::get<3>(result));

                                    // Ensure values are correclty copied
                                    ASSERT_TRUE(std::get<4>(result));
                                }

                            }

                            // Test with allocator with extra
                            {
                                auto test_with_allocator = [](const U* raw, usize element_count) {
                                    Array<T, HUD_TEST::ArrayAllocator<alignof(T)>> array(raw, element_count, extra, HUD_TEST::ArrayAllocator<alignof(T)>{});
                                    bool all_values_copied = true;

                                    // Ensure values are correclty copied
                                    for (usize index = 0; index < element_count; index++) {
                                        if (*(array.data() + index) != static_cast<T>(raw[index])) {
                                            all_values_copied = false;
                                            break;
                                        }
                                    }

                                    return std::tuple{
                                        // Allocation of 4 i32 should be done
                                        array.data() != nullptr,
                                        array.count(),
                                        array.max_count(),

                                        // Ensure it's not the same memory buffer
                                        (void*)array.data() != (void*)&raw[0],

                                        // Ensure values are correclty copied
                                        all_values_copied,

                                        // Ensure we are allocating only one time
                                        array.allocator().allocation_count(),
                                        array.allocator().free_count()
                                    };
                                };

                                // Non Constant
                                {
                                    constexpr usize element_count = 4;
                                    constexpr U raw[element_count] = { 1,2,3,4 };
                                    const auto result = test_with_allocator(raw, element_count);
                                    // Allocation of 4 i32 should be done
                                    ASSERT_TRUE(std::get<0>(result));
                                    ASSERT_EQ(std::get<1>(result), element_count);
                                    ASSERT_EQ(std::get<2>(result), element_count + extra);

                                    // Ensure it's not the same memory buffer
                                    ASSERT_TRUE(std::get<3>(result));

                                    // Ensure values are correclty copied
                                    ASSERT_TRUE(std::get<4>(result));

                                    // Ensure we are allocating only one time
                                    ASSERT_EQ(std::get<5>(result), 1u);
                                    ASSERT_EQ(std::get<6>(result), 0u);
                                }

                                // Constant
                                {
                                    constexpr usize element_count = 4;
                                    constexpr U raw[element_count] = { 1,2,3,4 };
                                    constexpr auto result = test_with_allocator(raw, element_count);

                                    // Allocation of 4 i32 should be done
                                    ASSERT_TRUE(std::get<0>(result));
                                    ASSERT_EQ(std::get<1>(result), element_count);
                                    ASSERT_EQ(std::get<2>(result), element_count + extra);

                                    // Ensure it's not the same memory buffer
                                    ASSERT_TRUE(std::get<3>(result));

                                    // Ensure values are correclty copied
                                    ASSERT_TRUE(std::get<4>(result));

                                    // Ensure we are allocating only one time
                                    ASSERT_EQ(std::get<5>(result), 1u);
                                    ASSERT_EQ(std::get<6>(result), 0u);
                                }
                            }
                    });
                }
            }
        });
    });

    ASSERT_EQ(at_least_one_copy_tested, true);

}

TEST(Array, construct_by_copying_raw_data_array_of_non_bitwise_copy_constructible_different_type)
{
    using namespace hud;

    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType;

    // test with default allocator no extra
    {
        auto test_default_allocator = [](const Type1* raw, usize element_count) {
            Array<Type2> array(raw, element_count);

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < element_count; index++) {
                if (array[index].id() != raw[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < element_count; index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != raw[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)&raw[0],

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called

            };
        };

        // Non Constant
        {
            constexpr usize element_count = 4;
            constexpr Type1 raw[element_count] = { 1,2,3,4 };
            const auto result = test_default_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }

        // Constant
        {
            constexpr usize element_count = 4;
            constexpr Type1 raw[element_count] = { 1,2,3,4 };
            constexpr auto result = test_default_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](const Type1* raw, usize element_count) {
            Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(raw, element_count, HUD_TEST::ArrayAllocator<alignof(Type2)>{});

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < element_count; index++) {
                if (array[index].id() != raw[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < element_count; index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != raw[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }
            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                array.data() != &raw[0],

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()

            };
        };

        // Non Constant
        {
            constexpr usize element_count = 4;
            constexpr Type1 raw[element_count] = { 1,2,3,4 };
            const auto result = test_with_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }

        // Constant
        {
            constexpr usize element_count = 4;
            constexpr Type1 raw[element_count] = { 1,2,3,4 };
            constexpr auto result = test_with_allocator(raw, element_count);
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), element_count);
            ASSERT_EQ(std::get<2>(result), element_count);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allcoator with extra
                {
                    auto test_default_allocator = [](const Type1* raw, usize element_count) {
                        Array<Type2> array(raw, element_count, extra);

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < element_count; index++) {
                            if (array[index].id() != raw[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < element_count; index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != raw[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != &raw[0],

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called

                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type1 raw[element_count] = { 1,2,3,4 };
                        const auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type1 raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_default_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }
                }


                // Test with allocator with extra
                {
                    auto test_with_allocator = [](const Type1* raw, usize element_count) {
                        Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(raw, element_count, extra, HUD_TEST::ArrayAllocator<alignof(Type2)>{});

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < element_count; index++) {
                            if (array[index].id() != raw[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < element_count; index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != raw[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }
                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != &raw[0],

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()

                        };
                    };

                    // Non Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type1 raw[element_count] = { 1,2,3,4 };
                        const auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr usize element_count = 4;
                        constexpr Type1 raw[element_count] = { 1,2,3,4 };
                        constexpr auto result = test_with_allocator(raw, element_count);
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), element_count);
                        ASSERT_EQ(std::get<2>(result), element_count + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, construct_with_initializer_list_of_bitwise_copy_constructible_same_type)
{
    using namespace hud;
    using Type = i32;

    static_assert(IsBitwiseCopyConstructibleV<Type>);

    {
        auto test_default_allocator = [](std::initializer_list<Type> initializer) {
            Array<Type> array(initializer);
            bool all_values_copied = true;

            // Ensure values are correclty copied
            for (usize index = 0; index < initializer.size(); index++) {
                if (*(array.data() + index) != *(initializer.begin() + index)) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied
                all_values_copied
            };
        };

        // Non Constant
        {
            const auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));
        }

        // Constant
        {
            constexpr auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](std::initializer_list<Type> initializer) {
            Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(initializer, HUD_TEST::ArrayAllocator<alignof(Type)>{});
            bool all_values_copied = true;

            // Ensure values are correclty copied
            for (usize index = 0; index < initializer.size(); index++) {
                if (*(array.data() + index) != *(initializer.begin() + index)) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                array.data() != initializer.begin(),

                // Ensure values are correclty copied
                all_values_copied,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };
        };

        // Non Constant
        {
            const auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allocator with extra
                {
                    auto test_default_allocator = [](std::initializer_list<Type> initializer) {
                        Array<Type> array(initializer, extra);
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (*(array.data() + index) != *(initializer.begin() + index)) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != initializer.begin(),

                            // Ensure values are correclty copied
                            all_values_copied
                        };

                    };
                    // Non Constant
                    {
                        const auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }

                }

                // Test with allocator with extra
                {
                    auto test_with_allocator = [](std::initializer_list<i32> initializer) {
                        Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(initializer, extra, HUD_TEST::ArrayAllocator<alignof(Type)>{});
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (*(array.data() + index) != *(initializer.begin() + index)) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            array.data() != initializer.begin(),

                            // Ensure values are correclty copied
                            all_values_copied,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()
                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_with_allocator({ 1,2,3,4 });

                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, construct_with_initializer_list_of_bitwise_copy_constructible_different_type)
{
    using namespace hud;
    using Type1 = i32;
    using Type2 = u32;

    static_assert(!std::is_same_v<Type1, Type2> && IsBitwiseCopyConstructibleV<Type2, Type1>);

    //test with default allocator no extra
    {
        auto test_default_allocator = [](std::initializer_list<Type1> initializer) {
            Array<Type2> array(initializer);
            bool all_values_copied = true;

            // Ensure values are correclty copied
            for (usize index = 0; index < initializer.size(); index++) {
                if (*(array.data() + index) != static_cast<Type2>(*(initializer.begin() + index))) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied
                all_values_copied
            };
        };

        // Non Constant
        {
            const auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));
        }

        // Constant
        {
            constexpr auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](std::initializer_list<Type1> initializer) {
            Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(initializer, HUD_TEST::ArrayAllocator<alignof(Type2)>{});
            bool all_values_copied = true;

            // Ensure values are correclty copied
            for (usize index = 0; index < initializer.size(); index++) {
                if (*(array.data() + index) != static_cast<Type2>(*(initializer.begin() + index))) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied
                all_values_copied,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()
            };
        };

        // Non Constant
        {
            const auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allocator with extra
                {
                    auto test_default_allocator = [](std::initializer_list<Type1> initializer) {
                        Array<Type2> array(initializer, extra);
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (*(array.data() + index) != static_cast<Type2>(*(initializer.begin() + index))) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied
                            all_values_copied
                        };

                    };
                    // Non Constant
                    {
                        const auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));
                    }

                }

                // Test with allocator with extra
                {
                    auto test_with_allocator = [](std::initializer_list<Type1> initializer) {
                        Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(initializer, extra, HUD_TEST::ArrayAllocator<alignof(Type2)>{});
                        bool all_values_copied = true;

                        // Ensure values are correclty copied
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (*(array.data() + index) != static_cast<Type2>(*(initializer.begin() + index))) {
                                all_values_copied = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied
                            all_values_copied,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()
                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_with_allocator({ 1,2,3,4 });

                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, construct_with_initializer_list_of_non_bitwise_copy_constructible_same_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    // test with default allocator no extra
    {
        auto test_default_allocator = [](std::initializer_list<Type> initializer) {
            Array<Type> array(initializer);

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (array[index].id() != initializer.begin()[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < initializer.size(); index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != initializer.begin()[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called

            };
        };

        // Non Constant
        {
            const auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }

        // Constant
        {
            constexpr auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](std::initializer_list<Type> initializer) {
            Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(initializer, HUD_TEST::ArrayAllocator<alignof(Type)>{});

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (array[index].id() != initializer.begin()[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < initializer.size(); index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != initializer.begin()[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }
            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()

            };
        };

        // Non Constant
        {
            const auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allcoator with extra
                {
                    auto test_default_allocator = [](std::initializer_list<Type> initializer) {
                        Array<Type> array(initializer, extra);

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (array[index].id() != initializer.begin()[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != initializer.begin()[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called

                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }
                }


                // Test with allocator with extra
                {
                    auto test_with_allocator = [](std::initializer_list<Type> initializer) {
                        Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>> array(initializer, extra, HUD_TEST::ArrayAllocator<alignof(Type)>{});

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (array[index].id() != initializer.begin()[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != initializer.begin()[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }
                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()

                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, construct_with_initializer_list_of_non_bitwise_copy_constructible_different_type)
{
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    static_assert(!std::is_same_v<Type1, Type2> && !IsBitwiseCopyConstructibleV<Type2, Type1>);

    // test with default allocator no extra
    {
        auto test_default_allocator = [](std::initializer_list<Type1> initializer) {
            Array<Type2> array(initializer);

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (array[index].id() != initializer.begin()[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < initializer.size(); index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != initializer.begin()[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called

            };
        };

        // Non Constant
        {
            const auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }

        // Constant
        {
            constexpr auto result = test_default_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));
        }
    }

    // test with allocator no extra
    {
        auto test_with_allocator = [](std::initializer_list<Type1> initializer) {
            Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(initializer, HUD_TEST::ArrayAllocator<alignof(Type2)>{});

            // Ensure values are correclty copied in order
            bool all_values_copied_in_order = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (array[index].id() != initializer.begin()[index].id()) {
                    all_values_copied_in_order = false;
                    break;
                }
            }

            // Ensure the copy constructor are called
            bool all_copy_constructor_are_called = true;
            for (usize index = 0; index < initializer.size(); index++) {
                // Ensure we call the copy constructor and the id is correctly copied
                if (array[index].copy_constructor_count() != 1u ||
                    array[index].id() != initializer.begin()[index].id()) {
                    all_copy_constructor_are_called = false;
                    break;
                }
            }
            return std::tuple{
                // Allocation of 4 i32 should be done
                array.data() != nullptr,
                array.count(),
                array.max_count(),

                // Ensure it's not the same memory buffer
                (void*)array.data() != (void*)initializer.begin(),

                // Ensure values are correclty copied in order
                all_values_copied_in_order,

                // Ensure the copy constructor are called
                all_copy_constructor_are_called,

                // Ensure we are allocating only one time
                array.allocator().allocation_count(),
                array.allocator().free_count()

            };
        };

        // Non Constant
        {
            const auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_with_allocator({ 1,2,3,4 });
            // Allocation of 4 i32 should be done
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u);

            // Ensure it's not the same memory buffer
            ASSERT_TRUE(std::get<3>(result));

            // Ensure values are correclty copied in order
            ASSERT_TRUE(std::get<4>(result));

            // Ensure the copy constructor are called
            ASSERT_TRUE(std::get<5>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<6>(result), 1u);
            ASSERT_EQ(std::get<7>(result), 0u);
        }
    }

    {
        HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
            []<usize extra>() {

            // Test default allcoator with extra
                {
                    auto test_default_allocator = [](std::initializer_list<Type1> initializer) {
                        Array<Type2> array(initializer, extra);

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (array[index].id() != initializer.begin()[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != initializer.begin()[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called

                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));
                    }
                }


                // Test with allocator with extra
                {
                    auto test_with_allocator = [](std::initializer_list<Type1> initializer) {
                        Array<Type2, HUD_TEST::ArrayAllocator<alignof(Type2)>> array(initializer, extra, HUD_TEST::ArrayAllocator<alignof(Type2)>{});

                        // Ensure values are correclty copied in order
                        bool all_values_copied_in_order = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (array[index].id() != initializer.begin()[index].id()) {
                                all_values_copied_in_order = false;
                                break;
                            }
                        }

                        // Ensure the copy constructor are called
                        bool all_copy_constructor_are_called = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            // Ensure we call the copy constructor and the id is correctly copied
                            if (array[index].copy_constructor_count() != 1u ||
                                array[index].id() != initializer.begin()[index].id()) {
                                all_copy_constructor_are_called = false;
                                break;
                            }
                        }
                        return std::tuple{
                            // Allocation of 4 i32 should be done
                            array.data() != nullptr,
                            array.count(),
                            array.max_count(),

                            // Ensure it's not the same memory buffer
                            (void*)array.data() != (void*)initializer.begin(),

                            // Ensure values are correclty copied in order
                            all_values_copied_in_order,

                            // Ensure the copy constructor are called
                            all_copy_constructor_are_called,

                            // Ensure we are allocating only one time
                            array.allocator().allocation_count(),
                            array.allocator().free_count()

                        };
                    };

                    // Non Constant
                    {
                        const auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_with_allocator({ 1,2,3,4 });
                        // Allocation of 4 i32 should be done
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + extra);

                        // Ensure it's not the same memory buffer
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure values are correclty copied in order
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure the copy constructor are called
                        ASSERT_TRUE(std::get<5>(result));

                        // Ensure we are allocating only one time
                        ASSERT_EQ(std::get<6>(result), 1u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                    }
                }
        });
    }
}

TEST(Array, copy_construct_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    /** The array we copy for test, we allocate also extra memory to test if we really copy the count(), not the max_count() elements */
    using Type = i32;

    static_assert(IsBitwiseCopyConstructibleV<Type>);

    using CopiedType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    HUD_TEST::for_each_type<HUD_TEST::ArrayAllocator<alignof(Type)>, HUD_TEST::ArrayAllocator2<alignof(Type)>>()([]<typename Allocator>() noexcept {

        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
            const CopiedType copied(initializer, copied_extra);

            // Copy the array
            Array<Type, Allocator> copy(copied);

            // Ensure we copy all datas in order
            bool all_values_copied = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (copy[index] != static_cast<Type>(index)) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Ensure we copy all datas in order
                copy.data() != nullptr,
                copy.count(),
                copy.max_count(),
                all_values_copied,

                // Ensure the copy data is not the same memory of the copied data
                copied.data() != copy.data(),

                // Ensure we are allocating only one time
                copy.allocator().allocation_count(),
                copy.allocator().free_count()
            };
        };

        // Non constant
        {
            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
            // Ensure we copy all datas in order
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u + 1u);
            ASSERT_TRUE(std::get<3>(result));

            // Ensure the copy data is not the same memory of the copied data
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
            // Ensure we copy all datas in order
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u + 1u);
            ASSERT_TRUE(std::get<3>(result));

            // Ensure the copy data is not the same memory of the copied data
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }


        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
            const CopiedType copied(initializer, copied_extra);

            // Copy the array
            Array<Type, Allocator> copy(copied, Allocator{});

            // Ensure we copy all datas in order
            bool all_values_copied = true;
            for (usize index = 0; index < initializer.size(); index++) {
                if (copy[index] != static_cast<Type>(index)) {
                    all_values_copied = false;
                    break;
                }
            }

            return std::tuple{
                // Ensure we copy all datas in order
                copy.data() != nullptr,
                copy.count(),
                copy.max_count(),
                all_values_copied,

                // Ensure the copy data is not the same memory of the copied data
                copied.data() != copy.data(),

                // Ensure we are allocating only one time
                copy.allocator().allocation_count(),
                copy.allocator().free_count()
            };
        };

        // Non constant
        {
            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
            // Ensure we copy all datas in order
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u + 1u);
            ASSERT_TRUE(std::get<3>(result));

            // Ensure the copy data is not the same memory of the copied data
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }

        // Constant
        {
            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
            // Ensure we copy all datas in order
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_EQ(std::get<1>(result), 4u);
            ASSERT_EQ(std::get<2>(result), 4u + 1u);
            ASSERT_TRUE(std::get<3>(result));

            // Ensure the copy data is not the same memory of the copied data
            ASSERT_TRUE(std::get<4>(result));

            // Ensure we are allocating only one time
            ASSERT_EQ(std::get<5>(result), 1u);
            ASSERT_EQ(std::get<6>(result), 0u);
        }


        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test with default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const CopiedType copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> copy(copied, extra);

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (copy[index] != static_cast<Type>(index)) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }

                    // Test with allocator
                    {
                        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const CopiedType copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> copy(copied, extra, Allocator{});

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (copy[index] != static_cast<Type>(index)) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, copy_construct_bitwise_copy_constructible_different_type)
{
    using namespace hud;
    /** The array we copy for test, we allocate also extra memory to test if we really copy the count(), not the max_count() elements */
    using Type1 = i32;
    using Type2 = u32;

    using AllocatorOfCopiedArray = HUD_TEST::ArrayAllocator<alignof(Type1)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type2)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfCopiedArray, OtherAllocatorOfArray>);
    static_assert(!std::is_same_v<Type1, Type2>);
    static_assert(IsBitwiseCopyConstructibleV<Type2, Type1>);


    HUD_TEST::for_each_type<AllocatorOfCopiedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test with default allocator no extra
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const Array<Type1, AllocatorOfCopiedArray> copied(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> copy(copied);

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (copy[index] != static_cast<Type2>(index)) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)copied.data() != (void*)copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }


        // Test with allocator no extra
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const Array<Type1, AllocatorOfCopiedArray> copied(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> copy(copied, Allocator{});

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (copy[index] != static_cast<Type2>(index)) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)copied.data() != (void*)copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test with default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const Array<Type1, AllocatorOfCopiedArray> copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> copy(copied, extra);

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (copy[index] != static_cast<Type2>(index)) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)copied.data() != (void*)copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }

                    // Test with allocator no extra
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const Array<Type1, AllocatorOfCopiedArray> copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> copy(copied, extra, Allocator{});

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (copy[index] != static_cast<Type2>(index)) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)copied.data() != (void*)copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, copy_construct_non_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    /** The array we copyfor test, we allocate also extra memory to test if we really copy the count(), not the max_count() elements */
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;
    using AllocatorOfCopiedArray = HUD_TEST::ArrayAllocator<alignof(Type)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfCopiedArray, OtherAllocatorOfArray>);
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    using CopiedType = const Array<HUD_TEST::NonBitwiseCopyConstructibleType, AllocatorOfCopiedArray>;

    HUD_TEST::for_each_type<AllocatorOfCopiedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const CopiedType copied(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> copy(copied);

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(copy[index].id()) != index ||
                        copy[index].copy_constructor_count() != 1u) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    copied.data() != copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        // Test with allocator
        {
            auto test_wtih_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const CopiedType copied(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> copy(copied, Allocator{});

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(copy[index].id()) != index ||
                        copy[index].copy_constructor_count() != 1u) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    copied.data() != copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_wtih_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_wtih_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const CopiedType copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> copy(copied, extra);

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(copy[index].id()) != index ||
                                    copy[index].copy_constructor_count() != 1u) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }


                    // Test with allocator
                    {
                        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const CopiedType copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> copy(copied, extra, Allocator{});

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(copy[index].id()) != index ||
                                    copy[index].copy_constructor_count() != 1u) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }

            });
        }
    });
}

TEST(Array, copy_construct_non_bitwise_copy_constructible_different_type)
{
    using namespace hud;


    /** The array we copyfor test, we allocate also extra memory to test if we really copy the count(), not the max_count() elements */
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using AllocatorOfCopiedArray = HUD_TEST::ArrayAllocator<alignof(Type1)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type2)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfCopiedArray, OtherAllocatorOfArray>);
    static_assert(!std::is_same_v<Type1, Type2>);
    static_assert(!IsBitwiseCopyConstructibleV<Type2, Type1>);

    HUD_TEST::for_each_type<AllocatorOfCopiedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const Array<Type1, AllocatorOfCopiedArray>  copied(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> copy(copied);

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(copy[index].id()) != index ||
                        copy[index].copy_constructor_count() != 1u) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    copied.data() != copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        // Test with allocator
        {
            auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                const Array<Type1, AllocatorOfCopiedArray>  copied(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> copy(copied, Allocator{});

                // Ensure we copy all datas in order
                bool all_values_copied = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(copy[index].id()) != index ||
                        copy[index].copy_constructor_count() != 1u) {
                        all_values_copied = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    copy.data() != nullptr,
                    copy.count(),
                    copy.max_count(),
                    all_values_copied,

                    // Ensure the copy data is not the same memory of the copied data
                    copied.data() != copy.data(),

                    // Ensure we are allocating only one time
                    copy.allocator().allocation_count(),
                    copy.allocator().free_count()
                };
            };

            // Non constant
            {
                const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const Array<Type1, AllocatorOfCopiedArray>  copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> copy(copied, extra);

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(copy[index].id()) != index ||
                                    copy[index].copy_constructor_count() != 1u) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }

                    // Test with allocator
                    {
                        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            const Array<Type1, AllocatorOfCopiedArray>  copied(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> copy(copied, extra, Allocator{});

                            // Ensure we copy all datas in order
                            bool all_values_copied = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(copy[index].id()) != index ||
                                    copy[index].copy_constructor_count() != 1u) {
                                    all_values_copied = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                copy.data() != nullptr,
                                copy.count(),
                                copy.max_count(),
                                all_values_copied,

                                // Ensure the copy data is not the same memory of the copied data
                                copied.data() != copy.data(),

                                // Ensure we are allocating only one time
                                copy.allocator().allocation_count(),
                                copy.allocator().free_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, move_construct_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    /** The array we move for test, we allocate also extra memory to test if we really move the count(), not the max_count() elements */
    using Type = i32;
    using AllocatorOfMovedArray = HUD_TEST::ArrayAllocator<alignof(Type)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfMovedArray, OtherAllocatorOfArray>);
    static_assert(IsBitwiseMoveConstructibleV<Type>);
    using MovedType = Array<Type, AllocatorOfMovedArray>;

    HUD_TEST::for_each_type<AllocatorOfMovedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test default allocator
        {

            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved));

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (move[index] != static_cast<Type>(index)) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    moved.data() != move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                // Bitwise copyable with same type should just stole the pointer without reallocating
                // If allocator are not the same, a reallocation is done to allocate with the correct allocator
                if (std::is_same_v<AllocatorOfMovedArray, Allocator>) {
                    ASSERT_EQ(std::get<5>(result), 0u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 1u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 0u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
                else {
                    ASSERT_EQ(std::get<5>(result), 1u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 0u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 1u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                // Bitwise copyable with same type should just stole the pointer without reallocating
                // If allocator are not the same, a reallocation is done to allocate with the correct allocator
                if (std::is_same_v<AllocatorOfMovedArray, Allocator>) {
                    ASSERT_EQ(std::get<5>(result), 0u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 1u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 0u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
                else {
                    ASSERT_EQ(std::get<5>(result), 1u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 0u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 1u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
            }
        }

        // Test with allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved), Allocator{});

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (move[index] != static_cast<Type>(index)) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    moved.data() != move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                    {

                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> move(std::move(moved), extra);

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (move[index] != static_cast<Type>(index)) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we allocate and free the moved array and just allocate the new array once
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we allocate and free the moved array and just allocate the new array once
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }

                    // Test with allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> move(std::move(moved), extra, Allocator{});

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (move[index] != static_cast<Type>(index)) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we allocate and free the moved array and just allocate the new array once
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we allocate and free the moved array and just allocate the new array once
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, move_construct_bitwise_move_constructible_different_type)
{
    using namespace hud;

    /** The array we move for test, we allocate also extra memory to test if we really move the count(), not the max_count() elements */
    using Type1 = i32;
    using Type2 = u32;
    using AllocatorOfMovedArray = HUD_TEST::ArrayAllocator<alignof(Type1)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type2)>;


    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfMovedArray, OtherAllocatorOfArray>);
    static_assert(!std::is_same_v<Type1, Type2>);
    static_assert(IsBitwiseMoveConstructibleV<Type2, Type1>);

    using MovedType = Array<Type1, AllocatorOfMovedArray>;

    HUD_TEST::for_each_type<AllocatorOfMovedArray, OtherAllocatorOfArray>()([]<typename Allocator>()noexcept {

        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> move(std::move(moved));

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (move[index] != index) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Bitwise moveable with same type should just stole the pointer without reallocating
                // If allocator are not the same, a reallocation is done to allocate with the correct allocator
                if (std::is_same_v<AllocatorOfMovedArray, Allocator>) {
                    ASSERT_EQ(std::get<5>(result), 0u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 1u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 0u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
                else {
                    ASSERT_EQ(std::get<5>(result), 1u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 0u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 1u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // We move bitwise move constructible of different type, we can't just still the buffer
                // ( Can't reinterpret_cast the pointer in constant evaluated fonction) so we have an allocation , move and free, always!
                // Allocator is move only if allocator are the same
                if (std::is_same_v<AllocatorOfMovedArray, Allocator>) {
                    ASSERT_EQ(std::get<5>(result), 1u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 1u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 1u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
                else {
                    ASSERT_EQ(std::get<5>(result), 1u);
                    ASSERT_EQ(std::get<6>(result), 0u);
                    ASSERT_EQ(std::get<7>(result), 0u);
                    ASSERT_EQ(std::get<8>(result), 0u);
                    ASSERT_EQ(std::get<9>(result), 1u);
                    ASSERT_EQ(std::get<10>(result), 1u);
                    ASSERT_EQ(std::get<11>(result), 0u);
                    ASSERT_EQ(std::get<12>(result), 0u);
                }
            }
        }

        // Test with allocator
        {
            auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> move(std::move(moved), Allocator{});

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (move[index] != index) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Providing an allocator force the realloation to be done with this allocator
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Providing an allocator force the realloation to be done with this allocator
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> move(std::move(moved), extra);

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (move[index] != index) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // With extra a eallocation is done to allocate with the correct allocator
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // With extra a eallocation is done to allocate with the correct allocator
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }

                    // Test with allocator
                    {
                        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type2, Allocator> move(std::move(moved), extra, Allocator{});

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (move[index] != index) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Providing an allocator force the realloation to be done with this allocator
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Providing an allocator force the realloation to be done with this allocator
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, move_construct_non_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    /** The array we move for test, we allocate also extra memory to test if we really move the count(), not the max_count() elements */
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    using AllocatorOfMovedArray = HUD_TEST::ArrayAllocator<alignof(Type)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfMovedArray, OtherAllocatorOfArray>);
    static_assert(!IsBitwiseMoveConstructibleV<Type>);

    using MovedType = Array<Type, AllocatorOfMovedArray>;

    HUD_TEST::for_each_type<AllocatorOfMovedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved));

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index ||
                        move[index].copy_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with allocator
        {
            auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved), Allocator{});

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index ||
                        move[index].copy_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                {
                    auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                        MovedType moved(initializer, copied_extra);

                        // Copy the array
                        Array<Type, Allocator> move(std::move(moved), extra);

                        // Ensure we moved all datas in order
                        bool all_values_moved = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (static_cast<usize>(move[index].id()) != index ||
                                move[index].copy_constructor_count() != 1u) {
                                all_values_moved = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Ensure we copy all datas in order
                            move.data() != nullptr,
                            move.count(),
                            move.max_count(),
                            all_values_moved,

                            // Ensure the copy data is not the same memory of the copied data
                            (void*)moved.data() != (void*)move.data(),

                            // Ensure we are allocating only one time
                            move.allocator().allocation_count(),
                            move.allocator().free_count(),
                            move.allocator().move_assign_count(),
                            move.allocator().move_construct_count(),
                            moved.allocator().allocation_count(),
                            moved.allocator().free_count(),
                            moved.allocator().move_assign_count(),
                            moved.allocator().move_construct_count()
                        };
                    };

                    // Non constant
                    {
                        const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }
                }

                // Test with allocator
                {
                    auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                        MovedType moved(initializer, copied_extra);

                        // Copy the array
                        Array<Type, Allocator> move(std::move(moved), extra, Allocator{});

                        // Ensure we moved all datas in order
                        bool all_values_moved = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (static_cast<usize>(move[index].id()) != index ||
                                move[index].copy_constructor_count() != 1u) {
                                all_values_moved = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Ensure we copy all datas in order
                            move.data() != nullptr,
                            move.count(),
                            move.max_count(),
                            all_values_moved,

                            // Ensure the copy data is not the same memory of the copied data
                            (void*)moved.data() != (void*)move.data(),

                            // Ensure we are allocating only one time
                            move.allocator().allocation_count(),
                            move.allocator().free_count(),
                            move.allocator().move_assign_count(),
                            move.allocator().move_construct_count(),
                            moved.allocator().allocation_count(),
                            moved.allocator().free_count(),
                            moved.allocator().move_assign_count(),
                            moved.allocator().move_construct_count()
                        };
                    };

                    // Non constant
                    {
                        const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }
                }
            });
        }
    });
}

TEST(Array, move_construct_non_bitwise_move_constructible_same_type)
{
    using namespace hud;

    /** The array we copy for test, we allocate also extra memory to test if we really copy the count(), not the max_count() elements */
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;
    using AllocatorOfMovedArray = HUD_TEST::ArrayAllocator<alignof(Type)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type)>;

    // Ensure we test with different allocator
    static_assert(!std::is_same_v<AllocatorOfMovedArray, OtherAllocatorOfArray>);
    static_assert(!IsBitwiseMoveConstructibleV<Type>);

    using MovedType = Array<Type, AllocatorOfMovedArray>;

    HUD_TEST::for_each_type<AllocatorOfMovedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {
        
        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved));

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index) {
                        all_values_moved = false;
                        break;
                    }
                    // MSVC call copy constructor instead of move constructor 
                    // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                    if (is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                        if (move[index].copy_constructor_count() != 1u) {
                            all_values_moved = false;
                            break;
                        }
                    }
                    else if (move[index].move_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with allocator
        {
            auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type, Allocator> move(std::move(moved), Allocator{});

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index) {
                        all_values_moved = false;
                        break;
                    }
                    // MSVC call copy constructor instead of move constructor 
                    // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                    if (is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                        if (move[index].copy_constructor_count() != 1u) {
                            all_values_moved = false;
                            break;
                        }
                    }
                    else if (move[index].move_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                    {
                        auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> move(std::move(moved), extra);

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(move[index].id()) != index) {
                                    all_values_moved = false;
                                    break;
                                }
                                // MSVC call copy constructor instead of move constructor 
                                // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                                if (hud::is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                                    if (move[index].copy_constructor_count() != 1u) {
                                        all_values_moved = false;
                                        break;
                                    }
                                }
                                else if (move[index].move_constructor_count() != 1u) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Always reallocate if types are non bitwise copy constructible types
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Always reallocate if types are non bitwise copy constructible types
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }

                    // Test with allocator
                    {
                        auto test_with_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                            MovedType moved(initializer, copied_extra);

                            // Copy the array
                            Array<Type, Allocator> move(std::move(moved), extra, Allocator{});

                            // Ensure we moved all datas in order
                            bool all_values_moved = true;
                            for (usize index = 0; index < initializer.size(); index++) {
                                if (static_cast<usize>(move[index].id()) != index) {
                                    all_values_moved = false;
                                    break;
                                }
                                // MSVC call copy constructor instead of move constructor 
                                // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                                if (hud::is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                                    if (move[index].copy_constructor_count() != 1u) {
                                        all_values_moved = false;
                                        break;
                                    }
                                }
                                else if (move[index].move_constructor_count() != 1u) {
                                    all_values_moved = false;
                                    break;
                                }
                            }

                            return std::tuple{
                                // Ensure we copy all datas in order
                                move.data() != nullptr,
                                move.count(),
                                move.max_count(),
                                all_values_moved,

                                // Ensure the copy data is not the same memory of the copied data
                                (void*)moved.data() != (void*)move.data(),

                                // Ensure we are allocating only one time
                                move.allocator().allocation_count(),
                                move.allocator().free_count(),
                                move.allocator().move_assign_count(),
                                move.allocator().move_construct_count(),
                                moved.allocator().allocation_count(),
                                moved.allocator().free_count(),
                                moved.allocator().move_assign_count(),
                                moved.allocator().move_construct_count()
                            };
                        };

                        // Non constant
                        {
                            const auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Always reallocate if types are non bitwise copy constructible types
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }

                        // Constant
                        {
                            constexpr auto result = test_with_allocator({ 0,1,2,3 }, 1u);
                            // Ensure we copy all datas in order
                            ASSERT_TRUE(std::get<0>(result));
                            ASSERT_EQ(std::get<1>(result), 4u);
                            ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                            ASSERT_TRUE(std::get<3>(result));

                            // Ensure the copy data is not the same memory of the copied data
                            ASSERT_TRUE(std::get<4>(result));

                            // Ensure we are allocating only one time of not
                            // Always reallocate if types are non bitwise copy constructible types
                            ASSERT_EQ(std::get<5>(result), 1u);
                            ASSERT_EQ(std::get<6>(result), 0u);
                            ASSERT_EQ(std::get<7>(result), 0u);
                            ASSERT_EQ(std::get<8>(result), 0u);
                            ASSERT_EQ(std::get<9>(result), 1u);
                            ASSERT_EQ(std::get<10>(result), 1u);
                            ASSERT_EQ(std::get<11>(result), 0u);
                            ASSERT_EQ(std::get<12>(result), 0u);
                        }
                    }
            });
        }
    });
}

TEST(Array, move_construct_non_bitwise_move_constructible_different_type)
{
    using namespace hud;


    /** The array we move for test, we allocate also extra memory to test if we really move the count(), not the max_count() elements */
    using Type1 = HUD_TEST::NonBitwiseMoveConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseMoveConstructibleType2;
    using AllocatorOfMovedArray = HUD_TEST::ArrayAllocator<alignof(Type1)>;
    using OtherAllocatorOfArray = HUD_TEST::ArrayAllocator2<alignof(Type2)>;

    // Ensure we test with different allocator and types
    static_assert(!std::is_same_v<AllocatorOfMovedArray, OtherAllocatorOfArray>);
    static_assert(!std::is_same_v<Type1, Type2>);
    static_assert(!IsBitwiseMoveConstructibleV<Type2, Type1>);

    using MovedType = Array<Type1, AllocatorOfMovedArray>;

    HUD_TEST::for_each_type<AllocatorOfMovedArray, OtherAllocatorOfArray>()([]<typename Allocator>() noexcept {

        // Test default allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> move(std::move(moved));

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index) {
                        all_values_moved = false;
                        break;
                    }
                    // MSVC call copy constructor instead of move constructor 
                    // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                    if (is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                        if (move[index].copy_constructor_count() != 1u) {
                            all_values_moved = false;
                            break;
                        }
                    }
                    else if (move[index].move_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test wtih allocator
        {
            auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                MovedType moved(initializer, copied_extra);

                // Copy the array
                Array<Type2, Allocator> move(std::move(moved), Allocator{});

                // Ensure we moved all datas in order
                bool all_values_moved = true;
                for (usize index = 0; index < initializer.size(); index++) {
                    if (static_cast<usize>(move[index].id()) != index) {
                        all_values_moved = false;
                        break;
                    }
                    // MSVC call copy constructor instead of move constructor 
                    // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                    if (is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                        if (move[index].copy_constructor_count() != 1u) {
                            all_values_moved = false;
                            break;
                        }
                    }
                    else if (move[index].move_constructor_count() != 1u) {
                        all_values_moved = false;
                        break;
                    }
                }

                return std::tuple{
                    // Ensure we copy all datas in order
                    move.data() != nullptr,
                    move.count(),
                    move.max_count(),
                    all_values_moved,

                    // Ensure the copy data is not the same memory of the copied data
                    (void*)moved.data() != (void*)move.data(),

                    // Ensure we are allocating only one time
                    move.allocator().allocation_count(),
                    move.allocator().free_count(),
                    move.allocator().move_assign_count(),
                    move.allocator().move_construct_count(),
                    moved.allocator().allocation_count(),
                    moved.allocator().free_count(),
                    moved.allocator().move_assign_count(),
                    moved.allocator().move_construct_count()
                };
            };

            // Non constant
            {
                const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }

            // Constant
            {
                constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                // Ensure we copy all datas in order
                ASSERT_TRUE(std::get<0>(result));
                ASSERT_EQ(std::get<1>(result), 4u);
                ASSERT_EQ(std::get<2>(result), 4u + 1u);
                ASSERT_TRUE(std::get<3>(result));

                // Ensure the copy data is not the same memory of the copied data
                ASSERT_TRUE(std::get<4>(result));

                // Ensure we are allocating only one time of not
                // Always reallocate if types are non bitwise copy constructible types
                ASSERT_EQ(std::get<5>(result), 1u);
                ASSERT_EQ(std::get<6>(result), 0u);
                ASSERT_EQ(std::get<7>(result), 0u);
                ASSERT_EQ(std::get<8>(result), 0u);
                ASSERT_EQ(std::get<9>(result), 1u);
                ASSERT_EQ(std::get<10>(result), 1u);
                ASSERT_EQ(std::get<11>(result), 0u);
                ASSERT_EQ(std::get<12>(result), 0u);
            }
        }

        // Test with extra
        {
            HUD_TEST::for_each_value<std::make_integer_sequence<usize, 5>>()(
                []<usize extra>() {

                // Test default allocator
                {
                    auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                        MovedType moved(initializer, copied_extra);

                        // Copy the array
                        Array<Type2, Allocator> move(std::move(moved), extra);

                        // Ensure we moved all datas in order
                        bool all_values_moved = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (static_cast<usize>(move[index].id()) != index) {
                                all_values_moved = false;
                                break;
                            }
                            // MSVC call copy constructor instead of move constructor 
                            // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                            if (hud::is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc)) {
                                if (move[index].copy_constructor_count() != 1u) {
                                    all_values_moved = false;
                                    break;
                                }
                            }
                            else if (move[index].move_constructor_count() != 1u) {
                                all_values_moved = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Ensure we copy all datas in order
                            move.data() != nullptr,
                            move.count(),
                            move.max_count(),
                            all_values_moved,

                            // Ensure the copy data is not the same memory of the copied data
                            (void*)moved.data() != (void*)move.data(),

                            // Ensure we are allocating only one time
                            move.allocator().allocation_count(),
                            move.allocator().free_count(),
                            move.allocator().move_assign_count(),
                            move.allocator().move_construct_count(),
                            moved.allocator().allocation_count(),
                            moved.allocator().free_count(),
                            moved.allocator().move_assign_count(),
                            moved.allocator().move_construct_count()
                        };
                    };

                    // Non constant
                    {
                        const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }
                }

                // Test wtih allocator
                {
                    auto test_default_allocator = [](std::initializer_list<i32> initializer, usize copied_extra) {
                        MovedType moved(initializer, copied_extra);

                        // Copy the array
                        Array<Type2, Allocator> move(std::move(moved), extra, Allocator{});

                        // Ensure we moved all datas in order
                        bool all_values_moved = true;
                        for (usize index = 0; index < initializer.size(); index++) {
                            if (static_cast<usize>(move[index].id()) != index) {
                                all_values_moved = false;
                                break;
                            }
                            // MSVC call copy constructor instead of move constructor 
                            // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
                            if (hud::is_constant_evaluated() && Compilation::is_compiler(ECompiler::msvc) ) {
                                if (move[index].copy_constructor_count() != 1u) {
                                    all_values_moved = false;
                                    break;
                                }
                            }
                            else if (move[index].move_constructor_count() != 1u) {
                                all_values_moved = false;
                                break;
                            }
                        }

                        return std::tuple{
                            // Ensure we copy all datas in order
                            move.data() != nullptr,
                            move.count(),
                            move.max_count(),
                            all_values_moved,

                            // Ensure the copy data is not the same memory of the copied data
                            (void*)moved.data() != (void*)move.data(),

                            // Ensure we are allocating only one time
                            move.allocator().allocation_count(),
                            move.allocator().free_count(),
                            move.allocator().move_assign_count(),
                            move.allocator().move_construct_count(),
                            moved.allocator().allocation_count(),
                            moved.allocator().free_count(),
                            moved.allocator().move_assign_count(),
                            moved.allocator().move_construct_count()
                        };
                    };

                    // Non constant
                    {
                        const auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }

                    // Constant
                    {
                        constexpr auto result = test_default_allocator({ 0,1,2,3 }, 1u);
                        // Ensure we copy all datas in order
                        ASSERT_TRUE(std::get<0>(result));
                        ASSERT_EQ(std::get<1>(result), 4u);
                        ASSERT_EQ(std::get<2>(result), 4u + 1u + extra);
                        ASSERT_TRUE(std::get<3>(result));

                        // Ensure the copy data is not the same memory of the copied data
                        ASSERT_TRUE(std::get<4>(result));

                        // Ensure we are allocating only one time of not
                        // Always reallocate if types are non bitwise copy constructible types
                        ASSERT_EQ(std::get<5>(result), 1u);
                        ASSERT_EQ(std::get<6>(result), 0u);
                        ASSERT_EQ(std::get<7>(result), 0u);
                        ASSERT_EQ(std::get<8>(result), 0u);
                        ASSERT_EQ(std::get<9>(result), 1u);
                        ASSERT_EQ(std::get<10>(result), 1u);
                        ASSERT_EQ(std::get<11>(result), 0u);
                        ASSERT_EQ(std::get<12>(result), 0u);
                    }
                }
            });
        }
    });
}


