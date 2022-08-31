#include <OSLayer/Memory.h>

#include "../Misc/LeakGuard.h"

TEST(Memory, destroy_trivial_type)
{
    using namespace hud;

    using Type = u32;
    using ResultType =u32;

    static_assert(std::is_trivial_v<Type>);

    auto test = []() -> ResultType {
        Type to_destroy = 15;
        Memory::destroy(to_destroy);
        return to_destroy;
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(result, 15u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(result, 15u);
    }
}

TEST(Memory, destroy_trivially_destructible_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = i32;

    static_assert(std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        Type to_destroy;
        to_destroy.i = 15;
        Memory::destroy(to_destroy);
        return to_destroy.i;
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

TEST(Memory, destroy_non_trivially_destructible_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    using ResultType = i32;
    
    static_assert(!std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        i32 is_destructor_called = 0;
        Type* to_destroy = Memory::allocate_array<Type>(1);
        HUD_TEST::LeakArrayGuard guard(to_destroy, 1);
        Memory::construct_at(to_destroy, &is_destructor_called);
        Memory::destroy(*to_destroy);
        return is_destructor_called;
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(result, 1);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(result, 1);
    }
}

TEST(Memory, destroy_array_trivial_type)
{
    using namespace hud;
    using Type = u32;
    using ResultType = std::tuple<u32, u32>;

    static_assert(std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        Type to_destroy[2] = { 15, 30 };
        Memory::destroy_array(to_destroy, 2);
        return { to_destroy[0], to_destroy[1] };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 30u);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15u);
        ASSERT_EQ(std::get<1>(result), 30u);
    }
}

TEST(Memory, destroy_array_trivially_destructible_type)
{
    using namespace hud;

    struct C {
        i32 i;
    };
    using Type = C;
    using ResultType = std::tuple<i32, i32>;
    static_assert(std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        Type to_destroy[2];
        to_destroy[0].i = 15;
        to_destroy[1].i = 30;
        Memory::destroy_array(to_destroy, 2);
        return { to_destroy[0].i, to_destroy[1].i };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 30);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 15);
        ASSERT_EQ(std::get<1>(result), 30);
    }
}

TEST(Memory, destroy_array_non_trivially_destructible_type)
{
    using namespace hud;
    
    using Type = HUD_TEST::SetBoolToTrueWhenDestroyed;
    using ResultType = std::tuple<i32, i32>;

    static_assert(!std::is_trivially_destructible_v<Type>);

    auto test = []() -> ResultType {
        i32 value[2] = { 0,0 };
        Type* to_destroy = Memory::allocate_array<Type>(2);
        HUD_TEST::LeakArrayGuard guard(to_destroy, 2);
        Memory::construct_array_at(to_destroy, to_destroy + 2);
        to_destroy[0].set_ptr(value);
        to_destroy[1].set_ptr(value + 1);
        Memory::destroy_array(to_destroy, 2);
        return { value[0], value[1] };
    };

    // Non constant
    {
        ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 1);
    }

    // Constant
    {
        constexpr ResultType result = test();
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 1);
    }
}