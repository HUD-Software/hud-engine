#include <OSLayer/Containers/Optional.h>
#include <optional>

TEST(Optional, less_or_equal_size_as_std_optional) {
    ASSERT_LE(sizeof(hud::Optional<i32>), sizeof(std::optional<i32>));
}

TEST(Optional, trivially_copy_constructible_if_type_is_trivially_copy_constructible) {
    using namespace hud;

    using Type = i32;

    ASSERT_TRUE(IsTriviallyCopyConstructibleV<Type>);
    ASSERT_TRUE(IsTriviallyCopyConstructibleV<Optional<Type>>);
}

TEST(Optional, not_trivially_copy_constructible_if_type_is_not_trivially_copy_constructible) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    ASSERT_FALSE(IsTriviallyCopyConstructibleV<Type>);
    ASSERT_FALSE(IsTriviallyCopyConstructibleV<Optional<Type>>);
}

TEST(Optional, trivially_destructible_if_type_is_trivially_destructible) {
    using namespace hud;

    using Type = i32;

    ASSERT_TRUE(IsTriviallyDestructibleV<Type>);
    ASSERT_TRUE(IsTriviallyDestructibleV<Optional<Type>>);
}

TEST(Optional, not_trivially_destructible_if_type_is_not_trivially_destructible) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    ASSERT_FALSE(IsTriviallyDestructibleV<Type>);
    ASSERT_FALSE(IsTriviallyDestructibleV<Optional<Type>>);
}

TEST(Optional, cast_bool) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option_empty;
        Optional<Type> option_non_empty{ inplace, 123, nullptr };
        return std::tuple{ static_cast<bool>(option_empty), static_cast<bool>(option_non_empty) };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}


TEST(Optional, has_value) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option_empty;
        Optional<Type> option_non_empty{ inplace, 123, nullptr };
        return std::tuple{ option_empty.has_value(), option_non_empty.has_value() };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}

TEST(Optional, value) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        
        Optional<Type> option_non_empty{ inplace, 123, nullptr };
        const Optional<Type> const_option_non_empty{ inplace, 123, nullptr };

        return std::tuple{
            // Value should return Lvalue reference
            IsLValueReferenceV<decltype(option_non_empty.value())> && 
            option_non_empty.value().id() == 123,
            // Value should return Lvalue reference to const
            IsLValueReferenceV<decltype(const_option_non_empty.value())> && 
            IsConstV<RemoveReferenceT<decltype(const_option_non_empty.value())>> && 
            const_option_non_empty.value().id() == 123,
            // Value should return Rvalue reference
            IsRValueReferenceV<decltype(forward<Optional<Type>>(option_non_empty).value())> &&
            move(option_non_empty).value().id() == 123,
            // Value should return Rvalue reference to const
            IsRValueReferenceV<decltype(forward<const Optional<Type>>(const_option_non_empty).value())> && 
            IsConstV<RemoveReferenceT<decltype(forward<const Optional<Type>>(const_option_non_empty).value())>> &&
            move(const_option_non_empty).value().id() == 123,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }
}

TEST(Optional, value_or) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option_empty;
        Optional<Type> option_non_empty{ inplace, 123, nullptr };
        const Optional<Type> const_option_empty;
        const Optional<Type> const_option_non_empty{ inplace, 123, nullptr };

        return std::tuple{
            option_empty.value_or(Type{456, nullptr}).id(),
            option_non_empty.value_or(Type{ 456, nullptr }).id(),
            const_option_empty.value_or(Type{ 456, nullptr }).id(),
            const_option_non_empty.value_or(Type{ 456, nullptr }).id(),
            move(option_empty).value_or(Type{456, nullptr}).id(),
            move(option_non_empty).value_or(Type{ 456, nullptr }).id(),
            move(const_option_empty).value_or(Type{ 456, nullptr }).id(),
            move(const_option_non_empty).value_or(Type{ 456, nullptr }).id()
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_EQ(std::get<0>(result), 456);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 456);
        ASSERT_EQ(std::get<3>(result), 123);
        ASSERT_EQ(std::get<4>(result), 456);
        ASSERT_EQ(std::get<5>(result), 123);
        ASSERT_EQ(std::get<6>(result), 456);
        ASSERT_EQ(std::get<7>(result), 123);
    }


    // Constant
    {
        constexpr auto result = test();
        ASSERT_EQ(std::get<0>(result), 456);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 456);
        ASSERT_EQ(std::get<3>(result), 123);
        ASSERT_EQ(std::get<4>(result), 456);
        ASSERT_EQ(std::get<5>(result), 123);
        ASSERT_EQ(std::get<6>(result), 456);
        ASSERT_EQ(std::get<7>(result), 123);
    }
}


TEST(Optional, operator_arrow) {

    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option{ inplace, 123, nullptr };
        const Optional<Type> const_option{ inplace, 456, nullptr };
        return std::tuple{
            option->id(),
            const_option->id()
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }
}

TEST(Optional, operator_dereference) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option{ inplace, 123, nullptr };
        const Optional<Type> const_option{ inplace, 456, nullptr };
        return std::tuple{
            (*option).id(),
            (*const_option).id()
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }
}
TEST(Optional, reset_on_empty_do_nothing) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option_empty;
        const bool has_value_before = option_empty.has_value();

        option_empty.reset();

        return std::tuple{
            has_value_before,
            option_empty.has_value(),
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }
}

TEST(Optional, reset_call_destructor_if_T_is_not_trivially_destructible) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyDestructibleV<Type>);

    const auto test = []() {
        i32 destructor_count;
        Optional<Type> option{ inplace, 123, &destructor_count };
        const bool has_value_before = option.has_value();
        const i32 destructor_count_before = destructor_count;

        option.reset();

        return std::tuple{
            has_value_before,
            destructor_count_before,
            option.has_value(),
            destructor_count
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0);
        ASSERT_FALSE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0);
        ASSERT_FALSE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1);
    }
}
