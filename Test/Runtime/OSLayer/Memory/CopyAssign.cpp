#include <OSLayer/Memory.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, copy_assign_array_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = std::tuple<u32, u32, u32, u32>;

    static_assert(std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type dest[2];
        Type src[2] = { 15, 32 };
        Memory::copy_assign_array(dest, src, 2);
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

TEST(Memory, copy_assign_array_bitwise_assignable_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };

    using Type = C;
    using ResultType = std::tuple<i32, i32, i32, i32>;

    static_assert(IsBitwiseCopyConstructibleV<C>);
    static_assert(IsBitwiseMoveConstructibleV<C>);

    auto test = []() -> ResultType {
        Type dest[2], src[2];
        dest[0].i = 0;
        dest[1].i = 0;
        src[0].i = 15;
        src[1].i = 32;
        Memory::copy_assign_array(dest, src, 2);
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

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 32);
        ASSERT_EQ(std::get<2>(result), 15);
        ASSERT_EQ(std::get<3>(result), 32);
    }
}

TEST(Memory, copy_assign_array_non_bitwise_copy_assignable_different_type)
{
    using namespace hud;

    using SourceType = HUD_TEST::NonBitwiseCopyAssignableType3;
    using DestinationType = HUD_TEST::NonBitwiseCopyAssignableType4;
    using ResultType = std::tuple<u32, u32, i32, u32, u32, i32>;

    static_assert(IsCopyConstructibleV<DestinationType, SourceType>);
    static_assert(!IsBitwiseCopyConstructibleV<DestinationType, SourceType>);
    static_assert(!std::is_same_v<DestinationType, SourceType>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        SourceType* src = Memory::allocate_array<SourceType>(2);
        HUD_TEST::LeakArrayGuard src_guard(src, 2);
        Memory::construct_array_at(src, src+2, &assign_counter);

        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard dest_guard(dest, 2);
        Memory::construct_array_at(dest, dest+2);

        Memory::copy_assign_array(dest, src, 2);
        return { dest[0].copy_constructor_count(), 
                 dest[0].copy_assign_count(),
                 dest[0].copy_order(),
                 dest[1].copy_constructor_count(),
                 dest[1].copy_assign_count(),
                 dest[1].copy_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 2);
    }
}

TEST(Memory, copy_assign_array_non_bitwise_copy_assignable_same_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType4;
    using ResultType = std::tuple<u32, u32, i32, u32, u32, i32>;
    
    static_assert(IsCopyAssignableV<Type>);
    static_assert(!IsBitwiseCopyAssignableV<Type>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src+2, & assign_counter);
        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::construct_array_at(dest, dest+2);

        Memory::copy_assign_array(dest, src, 2);

        return { dest[0].copy_constructor_count(),
                 dest[0].copy_assign_count(),
                 dest[0].copy_order(),
                 dest[1].copy_constructor_count(),
                 dest[1].copy_assign_count(),
                 dest[1].copy_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 2);
    }
}
