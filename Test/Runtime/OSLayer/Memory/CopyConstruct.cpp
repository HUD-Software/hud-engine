#include <OSLayer/Memory.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, copy_construct_array_trivial_type)
{
    using namespace hud;
    using Type = u32;
    using ResultType = std::tuple<u32, u32, u32, u32>;

    static_assert(std::is_trivially_copy_constructible_v<Type>);

    auto test = []() -> ResultType {
        Type dest[2];
        Type src[2] = { 15, 32 };
        Memory::copy_construct_array(dest, src, 2);
        return { dest[0], dest[1], src[0], src[1] };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 32u);
        ASSERT_EQ(std::get<2>(result), 15u);
        ASSERT_EQ(std::get<3>(result), 32u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 32u);
        ASSERT_EQ(std::get<2>(result), 15u);
        ASSERT_EQ(std::get<3>(result), 32u);
    }
}

TEST(Memory, copy_construct_array_bitwise_constructible_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = std::tuple<i32, i32, i32, i32>;

    static_assert(IsBitwiseCopyConstructibleV<Type>);

    auto test = []() -> ResultType {
        Type dest[2], src[2];
        dest[0].i = 0;
        dest[1].i = 0;
        src[0].i = 15;
        src[1].i = 32;
        Memory::copy_construct_array(dest, src, 2);
        return { dest[0].i, dest[1].i, src[0].i, src[1].i };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 32);
        ASSERT_EQ(std::get<2>(result), 15);
        ASSERT_EQ(std::get<3>(result), 32);
    }

    // Non constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 32);
        ASSERT_EQ(std::get<2>(result), 15);
        ASSERT_EQ(std::get<3>(result), 32);
    }
}

TEST(Memory, copy_construct_array_non_bitwise_constructible_different_type)
{
    using namespace hud;

    using SourceType = HUD_TEST::NonBitwiseCopyConstructibleType3;
    using DestinationType = HUD_TEST::NonBitwiseCopyConstructibleType4;
    using ResultType = std::tuple<i32, i32>;

    static_assert(IsCopyConstructibleV<DestinationType, SourceType>);
    static_assert(!IsBitwiseCopyConstructibleV<DestinationType, SourceType>);

    auto test = []() -> ResultType {

        i32 ctor_index = 0;
        SourceType* src = Memory::allocate_array<SourceType>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_index);

        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::copy_construct_array(dest, src, 2);
        return { dest[0].ctor_order() , dest[1].ctor_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 2);
    }
}

TEST(Memory, copy_construct_array_non_bitwise_constructible_same_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyConstructibleType4;
    using ResultType = std::tuple<u32, i32, u32, i32>;

    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    auto test = []() -> ResultType {
        i32 ctor_index = 0;
        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_index);
        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::copy_construct_array(dest, src, 2);
        return { dest[0].copy_constructor_count(),
                 dest[0].ctor_order(),
                 dest[1].copy_constructor_count(),
                 dest[1].ctor_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 1);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 1);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 2);
    }
}