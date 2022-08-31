#include <OSLayer/Memory.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, default_construct_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = u32;
    static_assert(std::is_trivial_v<Type>);

    auto test = []()-> ResultType {
        Type to_construct;
        Memory::default_construct(&to_construct);
        return to_construct;
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(result, 0u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(result, 0u);
    }
}

TEST(Memory, default_construct_trivial_constructible_type)
{
    using namespace hud;

    struct C {
        i32 value;
    };
    using Type = C;
    using ResultType = i32;

    static_assert(std::is_trivial_v<Type>);

    auto test = []()-> ResultType {
        Type* to_construct = Memory::allocate_array<Type>(1);
        HUD_TEST::LeakArrayGuard guard(to_construct, 1);
        Memory::default_construct(to_construct);
        return to_construct->value;
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(result, 0);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(result, 0);
    }
}

TEST(Memory, default_construct_non_trivial_constructible_type)
{
    using namespace hud;

    struct C {
        i32 value = 15;
    };
    using Type = C;
    using ResultType = i32;

    static_assert(!std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type* to_construct = Memory::allocate_array<Type>(1);
        HUD_TEST::LeakArrayGuard guard(to_construct, 1);
        Memory::default_construct(to_construct);
        return to_construct->value;
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(result, 15);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(result, 15);
    }
}

TEST(Memory, default_construct_array_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType = std::tuple <u32, u32>;

    static_assert(std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type to_construct[2];
        Memory::default_construct_array(to_construct, to_construct + 2);
        return { to_construct[0], to_construct[1] };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<0>(result), 0u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<0>(result), 0u);
    }
}

TEST(Memory, default_construct_array_trivial_constructible_type)
{
    using namespace hud;

    struct C {
        i32 value;
    };
    using Type = C;
    using ResultType = std::tuple <i32, i32>;

    static_assert(std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type* to_construct = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard(to_construct, 2);
        Memory::default_construct_array(to_construct, to_construct + 2);
        return { to_construct[0].value, to_construct[1].value };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0);
        ASSERT_EQ(std::get<0>(result), 0);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 0);
        ASSERT_EQ(std::get<0>(result), 0);
    }
}

TEST(Memory, default_construct_array_non_trivial_constructible_type)
{
    using namespace hud;

    struct C {
        i32 value = 15;
    };
    using Type = C;
    using ResultType = std::tuple <i32, i32>;

    static_assert(!std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type* to_construct = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard(to_construct, 2);
        Memory::default_construct_array(to_construct, to_construct + 2);
        return { to_construct[0].value, to_construct[1].value };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<0>(result), 15);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<0>(result), 15);
    }
}