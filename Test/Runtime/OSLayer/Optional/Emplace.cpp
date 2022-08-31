#include <OSLayer/Containers/Optional.h>
#include <OSLayer/Traits/IsTriviallyCopyConstructible.h>

TEST(Optional, emplace_move_inplace) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsConstructibleV<Type, i32, i32*>);

    const auto test = [](const i32 value) {
        i32 destructor_count;
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        
        option.emplace(value, &destructor_count);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().constructor_count(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0);
    }
}

TEST(Optional, emplace_call_destructor) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsConstructibleV<Type, i32, i32*>);

    const auto test = [](const i32 value) {
        i32 destructor_count{ 0 };
        i32 other_destructor_count{ 0 };
        Optional<Type> option{ inplace, value, &destructor_count };

        option.emplace(value, &other_destructor_count);

        return std::tuple{ destructor_count, other_destructor_count };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_EQ(std::get<0>(result), 1);
        ASSERT_EQ(std::get<1>(result), 0);
    }
}
TEST(Optional, emplace_by_copy_in_empty_trivially_copy_constructible) {
    using namespace hud;
    using Type = i32;
   
    static_assert(IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        option.emplace(value);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, emplace_by_copy_in_non_empty_trivially_copy_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const Type before, const Type after) {
        Optional<Type> option{ before };

        const bool has_value_before = option.has_value();
        const Type value_before = option.value();

        option.emplace(after);

        return std::tuple{
            has_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123,456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, emplace_by_copy_in_empty_non_trivially_copy_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();
        
        const Type other{ value };
        option.emplace(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
    }
}

TEST(Optional, emplace_by_copy_in_non_empty_non_trivially_copy_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ inplace, before };

        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();

        const Type other{ after };
        option.emplace(other);

        return std::tuple{
            has_value_before,
            value_before,
            option.has_value(),
            option.value().id()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, emplace_by_copy_in_empty_trivially_move_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        option.emplace(value);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, emplace_by_copy_in_non_empty_trivially_move_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const Type before, const Type after) {
        Optional<Type> option{ before };

        const bool has_value_before = option.has_value();
        const Type value_before = option.value();

        option.emplace(after);

        return std::tuple{
            has_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, emplace_by_copy_in_empty_non_trivially_move_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        const Type other{ value };
        option.emplace(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
    }
}

TEST(Optional, emplace_by_copy_in_non_empty_non_trivially_move_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ inplace, before };

        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_ctor_count_before = option.value().copy_constructor_count();
        const u32 move_ctor_count_before = option.value().move_constructor_count();

        const Type other{ after };
        option.emplace(other);

        return std::tuple{
            has_value_before,
            value_before,
            copy_ctor_count_before,
            move_ctor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_EQ(std::get<5>(result), 456);
        ASSERT_EQ(std::get<6>(result), 1u);
        ASSERT_EQ(std::get<7>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_EQ(std::get<5>(result), 456);
        ASSERT_EQ(std::get<6>(result), 1u);
        ASSERT_EQ(std::get<7>(result), 0u);
    }
}

TEST(Optional, emplace_by_move_in_empty_trivially_copy_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](Type value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        option.emplace(hud::move(value));

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, emplace_by_move_in_non_empty_trivially_copy_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const Type before, Type after) {
        Optional<Type> option{ before };

        const bool has_value_before = option.has_value();
        const Type value_before = option.value();

        option.emplace(hud::move(after));

        return std::tuple{
            has_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, emplace_by_move_in_empty_non_trivially_copy_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    const auto test = [](const i32 value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        Type other{ value };
        option.emplace(hud::move(other));

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 1u);
    }
}

TEST(Optional, emplace_by_move_in_non_empty_non_trivially_copy_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ inplace, before };

        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 ctor_before = option.value().copy_constructor_count();

        Type other{ after };
        option.emplace(hud::move(other));

        return std::tuple{
            has_value_before,
            value_before,
            ctor_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_EQ(std::get<4>(result), 456);
        ASSERT_EQ(std::get<5>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_EQ(std::get<4>(result), 456);
        ASSERT_EQ(std::get<5>(result), 1u);
    }
}

TEST(Optional, emplace_by_move_in_empty_trivially_move_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        option.emplace(hud::move(value));

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, emplace_by_move_in_non_empty_trivially_move_constructible) {
    using namespace hud;
    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const Type before, Type after) {
        Optional<Type> option{ before };

        const bool has_value_before = option.has_value();
        const Type value_before = option.value();

        option.emplace(hud::move(after));

        return std::tuple{
            has_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, emplace_by_move_in_empty_non_trivially_move_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;

        const bool has_value_before = option.has_value();

        Type other{ value };
        option.emplace(hud::move(other));

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
    }
}

TEST(Optional, emplace_by_move_in_non_empty_non_trivially_move_constructible) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ inplace, before };

        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_ctor_count_before = option.value().copy_constructor_count();
        const u32 move_ctor_count_before = option.value().move_constructor_count();

        Type other{ after };
        option.emplace(hud::move(other));

        return std::tuple{
            has_value_before,
            value_before,
            copy_ctor_count_before,
            move_ctor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count()
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_EQ(std::get<5>(result), 456);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_EQ(std::get<5>(result), 456);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
    }
}