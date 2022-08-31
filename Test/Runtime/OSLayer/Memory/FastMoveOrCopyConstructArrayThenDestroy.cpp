#include <OSLayer/Memory.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, fast_move_or_copy_construct_array_then_destroy_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = std::tuple<u32, u32, u32, u32>;

    static_assert(std::is_trivially_copy_constructible_v<Type>);
    static_assert(std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        Type dest[2];
        Type src[2] = { 15, 32 };
        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
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

TEST(Memory, fast_move_or_copy_construct_array_then_destroy_bitwise_constructible_and_destructible_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = std::tuple<i32, i32, i32, i32>;

    static_assert(IsBitwiseCopyConstructibleV<C>);
    static_assert(IsBitwiseMoveConstructibleV<C>);
    static_assert(IsTriviallyDestructibleV<C>);

    auto test = []() -> ResultType {
        Type dest[2], src[2];
        dest[0].i = 0;
        dest[1].i = 0;
        src[0].i = 15;
        src[1].i = 32;
        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
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

TEST(Memory, fast_move_or_copy_construct_array_then_destroy_non_bitwise_copy_constructible_and_destructible_different_type)
{
    using namespace hud;

    struct SourceType : public HUD_TEST::NonBitwiseCopyConstructibleType3, HUD_TEST::SetBoolToTrueWhenDestroyed {
        constexpr SourceType(i32* ctor_order, i32* dtor_order) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType3(ctor_order)
            , HUD_TEST::SetBoolToTrueWhenDestroyed(dtor_order) {
        }

        constexpr ~SourceType() = default;
    };

    struct DestinationType : public HUD_TEST::NonBitwiseCopyConstructibleType4 {
        constexpr DestinationType(const SourceType& other) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType4(other) {
        }
    };

    using ResultType = std::tuple<u32, i32, u32, i32>;

    static_assert(IsCopyConstructibleV<DestinationType, SourceType>);
    static_assert(!IsBitwiseCopyConstructibleV<DestinationType, SourceType>);

    auto test = []() -> ResultType {
        i32 ctor_order = 0;
        i32 dtor_order = 0;

        SourceType* src = Memory::allocate_array<SourceType>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_order, &dtor_order);

        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);

        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
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

TEST(Memory, fast_move_or_copy_construct_then_destroy_non_bitwise_move_constructible_and_destructible_different_type)
{
    using namespace hud;

    struct SourceType : public HUD_TEST::NonBitwiseMoveConstructibleType3, HUD_TEST::SetBoolToTrueWhenDestroyed {
        constexpr SourceType(i32* ctor_order, i32* dtor_order) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType3(ctor_order)
            , HUD_TEST::SetBoolToTrueWhenDestroyed(dtor_order) {
        }

        constexpr ~SourceType() = default;
    };

    struct DestinationType : public HUD_TEST::NonBitwiseMoveConstructibleType4 {
        constexpr DestinationType(SourceType&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType4(std::forward<HUD_TEST::NonBitwiseMoveConstructibleType3>(other)) {
        }

        // MSVC call copy constructor instead of move constructor 
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        constexpr DestinationType(const SourceType& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType4(other) {
        }
    };

    using ResultType = std::tuple<u32, u32, i32, u32, u32, i32>;
    static_assert(IsMoveConstructibleV<DestinationType, SourceType>);
    static_assert(!IsBitwiseMoveConstructibleV<DestinationType, SourceType>);
    static_assert(IsDestructibleV<SourceType>);
    static_assert(!IsTriviallyDestructibleV<SourceType>);

    auto test = []() -> ResultType {
        i32 ctor_order = 0;
        i32 dtor_order = 0;

        SourceType* src = Memory::allocate_array<SourceType>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_order, &dtor_order);

        DestinationType* dest = Memory::allocate_array<DestinationType>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);

        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
        return { dest[0].move_constructor_count(),
                 dest[0].copy_constructor_count(),
                 dest[0].ctor_order(),
                 dest[1].move_constructor_count(),
                 dest[1].copy_constructor_count(),
                 dest[1].ctor_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();
        // MSVC call copy constructor instead of move constructor
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        if constexpr (Compilation::is_compiler(ECompiler::msvc)) {
            ASSERT_EQ(std::get<0>(result), 0u);
            ASSERT_EQ(std::get<1>(result), 1u);
        }
        else {
            ASSERT_EQ(std::get<0>(result), 1u);
            ASSERT_EQ(std::get<1>(result), 0u);
        }
        ASSERT_EQ(std::get<2>(result), 1);

        // MSVC call copy constructor instead of move constructor
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        if constexpr (Compilation::is_compiler(ECompiler::msvc)) {
            ASSERT_EQ(std::get<3>(result), 0u);
            ASSERT_EQ(std::get<4>(result), 1u);
        }
        else {
            ASSERT_EQ(std::get<3>(result), 1u);
            ASSERT_EQ(std::get<4>(result), 0u);
        }
        ASSERT_EQ(std::get<5>(result), 2);
    }
}

TEST(Memory, fast_move_or_copy_construct_array_then_destroy_non_bitwise_copy_constructible_and_destructible_same_type)
{
    using namespace hud;

    struct Type : public HUD_TEST::NonBitwiseCopyConstructibleType4, HUD_TEST::SetBoolToTrueWhenDestroyed {
        constexpr Type(i32* ctor_order, i32* dtor_order) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType4(ctor_order)
            , HUD_TEST::SetBoolToTrueWhenDestroyed(dtor_order) {
        }

        constexpr ~Type() = default;
    };

    using ResultType = std::tuple<u32, i32, u32, i32>;
    static_assert(IsCopyConstructibleV<Type>);
    static_assert(!IsBitwiseCopyConstructibleV<Type>);
    static_assert(IsDestructibleV<Type>);
    static_assert(!IsTriviallyDestructibleV<Type>);


    auto test = []() -> ResultType {
        i32 ctor_order = 0;
        i32 dtor_order = 0;

        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_order, &dtor_order);

        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);

        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
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

TEST(Memory, fast_move_or_copy_construct_array_then_destroy_non_bitwise_move_constructible_and_destructible_same_type)
{
    using namespace hud;

    struct Type : public HUD_TEST::NonBitwiseMoveConstructibleType4, HUD_TEST::SetBoolToTrueWhenDestroyed {
        constexpr Type(i32* ctor_order, i32* dtor_order) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType4(ctor_order)
            , HUD_TEST::SetBoolToTrueWhenDestroyed(dtor_order) {
        }

        // MSVC call copy constructor instead of move constructor 
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        constexpr Type(const Type& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType4(other)
            , HUD_TEST::SetBoolToTrueWhenDestroyed(other) {
        }

        constexpr Type(Type&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType4(std::forward<HUD_TEST::NonBitwiseMoveConstructibleType4>(other))
            , HUD_TEST::SetBoolToTrueWhenDestroyed(std::forward<HUD_TEST::SetBoolToTrueWhenDestroyed>(other)) {
        }

        constexpr ~Type() = default;
    };

    using ResultType = std::tuple<u32, u32, i32, u32, u32, i32>;
    static_assert(IsMoveConstructibleV<Type>);
    static_assert(!IsBitwiseMoveConstructibleV<Type>);
    static_assert(IsDestructibleV<Type>);
    static_assert(!IsTriviallyDestructibleV<Type>);


    auto test = []() -> ResultType {
        i32 ctor_order = 0;
        i32 dtor_order = 0;

        Type* src = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_src(src, 2);
        Memory::construct_array_at(src, src + 2, &ctor_order, &dtor_order);

        Type* dest = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard_dest(dest, 2);

        Memory::fast_move_or_copy_construct_array_then_destroy(dest, src, 2);
        return { dest[0].move_constructor_count(),
                 dest[0].copy_constructor_count(),
                 dest[0].ctor_order(),
                 dest[1].move_constructor_count(),
                 dest[1].copy_constructor_count(),
                 dest[1].ctor_order() };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 2);
    }

    // Constant
    {
        constexpr ResultType result = test();

        // MSVC call copy constructor instead of move constructor 
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        if constexpr (Compilation::is_compiler(ECompiler::msvc)) {
            ASSERT_EQ(std::get<0>(result), 0u);
            ASSERT_EQ(std::get<1>(result), 1u);
        }
        else {
            ASSERT_EQ(std::get<0>(result), 1u);
            ASSERT_EQ(std::get<1>(result), 0u);
        }
        ASSERT_EQ(std::get<2>(result), 1);

        // MSVC call copy constructor instead of move constructor 
        // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
        if constexpr (Compilation::is_compiler(ECompiler::msvc)) {
            ASSERT_EQ(std::get<3>(result), 0u);
            ASSERT_EQ(std::get<4>(result), 1u);
        }
        else {
            ASSERT_EQ(std::get<3>(result), 1u);
            ASSERT_EQ(std::get<4>(result), 0u);
        }
        ASSERT_EQ(std::get<5>(result), 2);
    }
}
