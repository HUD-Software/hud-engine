#include <OSLayer/Memory.h>
#include <OSLayer/Traits/IsTrivial.h>
#include <OSLayer/Traits/IsBitwiseCopyAssignable.h>
#include <OSLayer/Traits/IsBitwiseMoveAssignable.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, move_or_copy_assign_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = std::tuple<u32, u32>;

    static_assert(IsTrivialV<Type>);

    auto test = []() -> ResultType {
        Type dest;
        Type src = 15;
        Memory::move_or_copy_assign(&dest, hud::move(src));
        return { dest, src };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 15u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 15u);
    }
}

TEST(Memory, move_or_copy_assign_bitwise_assignable_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = std::tuple<i32, i32>;

    static_assert(IsBitwiseCopyAssignableV<Type>);
    static_assert(IsBitwiseMoveAssignableV<Type>);

    auto test = []() -> ResultType {
        Type dest, src;
        dest.i = 0;
        src.i = 15;
        Memory::move_or_copy_assign(&dest, hud::move(src));
        return { dest.i, src.i };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 15);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 15);
    }
}

TEST(Memory, move_or_copy_assign_non_bitwise_copy_assignable_different_type)
{
    using namespace hud;

    using SourceType = HUD_TEST::NonBitwiseCopyAssignableType3;
    using DestinationType = HUD_TEST::NonBitwiseCopyAssignableType4;
    using ResultType = std::tuple<u32, u32, i32>;

    static_assert(IsCopyAssignableV<DestinationType, SourceType>);
    static_assert(!IsBitwiseCopyAssignableV<DestinationType, SourceType>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        SourceType* src = Memory::allocate_array<SourceType>(1);
        HUD_TEST::LeakArrayGuard guard_src(src, 1);
        Memory::construct_at(src, &assign_counter);
        DestinationType* dest = Memory::allocate_array<DestinationType>(1);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 1);
        Memory::construct_at(dest);

        Memory::move_or_copy_assign(dest, hud::move(*src));
        return { dest->copy_constructor_count(),
                 dest->copy_assign_count(),
                 dest->copy_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
    }
}

TEST(Memory, move_or_copy_assign_non_bitwise_move_assignable_different_type)
{
    using namespace hud;

    using SourceType = HUD_TEST::NonBitwiseMoveAssignableType3;
    using DestinationType = HUD_TEST::NonBitwiseMoveAssignableType4;
    using ResultType = std::tuple<u32, u32, u32, u32, i32>;

    static_assert(IsMoveAssignableV<DestinationType, SourceType>);
    static_assert(!IsBitwiseMoveAssignableV<DestinationType, SourceType>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        SourceType* src = Memory::allocate_array<SourceType>(1);
        HUD_TEST::LeakArrayGuard guard_src(src, 1);
        Memory::construct_at(src, &assign_counter);
        DestinationType* dest = Memory::allocate_array<DestinationType>(1);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 1);
        Memory::construct_at(dest);

        Memory::move_or_copy_assign(dest, hud::move(*src));
        return { dest->copy_constructor_count(),
                 dest->move_constructor_count(),
                 dest->move_assign_count(),
                 dest->copy_assign_count(),
                 dest->move_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1);
    }
}

TEST(Memory, move_or_copy_assign_non_bitwise_copy_assignable_same_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType4;
    using ResultType = std::tuple<u32, u32, i32>;

    static_assert(IsCopyConstructibleV<Type>);
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        Type* src = Memory::allocate_array<Type>(1);
        HUD_TEST::LeakArrayGuard guard_src(src, 1);
        Memory::construct_at(src, &assign_counter);
        Type* dest = Memory::allocate_array<Type>(1);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 1);
        Memory::construct_at(dest);

        Memory::move_or_copy_assign(dest, hud::move(*src));
        return { dest->copy_constructor_count(),
                 dest->copy_assign_count(),
                 dest->copy_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 1);
    }
}

TEST(Memory, move_or_copy_assign_array_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = std::tuple<u32, u32, u32, u32>;

    static_assert(std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type dest[2];
        Type src[2] = { 15, 32 };
        Memory::move_or_copy_assign_array(dest, src, src+2);
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

TEST(Memory, move_or_copy_assign_array_bitwise_assignable_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = std::tuple<i32, i32>;

    static_assert(IsBitwiseCopyAssignableV<Type>);
    static_assert(IsBitwiseMoveAssignableV<Type>);

    auto test = []() -> ResultType {
        Type dest[2], src[2];
        dest[0].i = 0;
        dest[1].i = 0;
        src[0].i = 15;
        src[1].i = 32;
        Memory::move_or_copy_assign_array(dest, src, src+2);
        return { dest[0].i, dest[1].i };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 32);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 32);
    }
}

TEST(Memory, move_or_copy_assign_array_non_bitwise_copy_assignable_different_type)
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
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &assign_counter);
        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::construct_array_at(dest, dest + 2);

        Memory::move_or_copy_assign_array(dest, src, src+2);
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

TEST(Memory, move_or_copy_assign_array_non_bitwise_move_assignable_different_type)
{
    using namespace hud;

    using SourceType = HUD_TEST::NonBitwiseMoveAssignableType3;
    using DestinationType = HUD_TEST::NonBitwiseMoveAssignableType4;
    using ResultType = std::tuple<u32, u32, u32, u32, i32, u32, u32, u32, u32, i32>;

    static_assert(IsMoveConstructibleV<DestinationType, SourceType>);
    static_assert(!IsBitwiseMoveConstructibleV<DestinationType, SourceType>);
    static_assert(!std::is_same_v<DestinationType, SourceType>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        SourceType* src = Memory::allocate_array<SourceType>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &assign_counter);
        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::construct_array_at(dest, dest + 2);

        Memory::move_or_copy_assign_array(dest, src, src+2);

        return { dest[0].copy_constructor_count(),
                 dest[0].move_constructor_count(),
                 dest[0].copy_assign_count(),
                 dest[0].move_assign_count(),
                 dest[0].move_order(),
                 dest[1].copy_constructor_count(),
                 dest[1].move_constructor_count(),
                 dest[1].copy_assign_count(),
                 dest[1].move_assign_count(),
                 dest[1].move_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2);
    }
}

TEST(Memory, move_or_copy_assign_array_non_bitwise_copy_constructible_same_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType4;
    using ResultType = std::tuple<u32, u32, i32, u32, u32, i32>;

    static_assert(IsCopyConstructibleV<Type>);
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &assign_counter);
        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::construct_array_at(dest, dest + 2);

        Memory::move_or_copy_assign_array(dest, src, src+2);
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

TEST(Memory, move_or_copy_assign_array_non_bitwise_move_constructible_same_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType4;
    using ResultType = std::tuple<u32, u32, u32, u32, i32, u32, u32, u32, u32, i32>;

    static_assert(IsMoveConstructibleV<Type>);
    static_assert(!IsBitwiseMoveConstructibleV<Type>);

    auto test = []() -> ResultType {
        i32 assign_counter = 0;
        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &assign_counter);
        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);
        Memory::construct_array_at(dest, dest + 2);

        Memory::move_or_copy_assign_array(dest, src, src+2);

        return { dest[0].copy_constructor_count(),
                 dest[0].move_constructor_count(),
                 dest[0].copy_assign_count(),
                 dest[0].move_assign_count(),
                 dest[0].move_order(),
                 dest[1].copy_constructor_count(),
                 dest[1].move_constructor_count(),
                 dest[1].copy_assign_count(),
                 dest[1].move_assign_count(),
                 dest[1].move_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2);
    }
}
