#include <OSLayer/Containers/Optional.h>
#include <OSLayer/Traits/IsTriviallyDefaultConstructible.h>
#include <optional>
TEST(Optional, default_constructor_trivially_default_constructible_type)
{
    using namespace hud;

    using Type = i32;
    static_assert(IsTriviallyDefaultConstructibleV<Type>);

    static_assert(!IsTriviallyDefaultConstructibleV<Optional<Type>>);
    static_assert(IsTriviallyDefaultConstructibleV<Optional<Type>> == IsTriviallyDefaultConstructibleV<std::optional<Type>>);

    auto test = []() {
        Optional<Type> option;
        return option.has_value();
    };

    // Non constant
    {
        ASSERT_FALSE(test());
    }

    // Constant
    {
        constexpr bool has_value = test();
        ASSERT_FALSE(has_value);
    }
}

TEST(Optional, default_constructor_non_trivially_default_constructible_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyDefaultConstructibleV<Type>);

    // If Optional<Type> is not trivially default constructible
    // std::optional<Type> is also non trivially default constructible
    static_assert(!IsTriviallyDefaultConstructibleV<Optional<Type>>);
    static_assert(IsTriviallyDefaultConstructibleV<Optional<Type>> == IsTriviallyDefaultConstructibleV<std::optional<Type>>);

    auto test = []() {
        Optional<Type> option;
        return option.has_value();
    };

    // Non constant
    {
        ASSERT_FALSE(test());
    }

    // Constant
    {
        constexpr bool has_value = test();
        ASSERT_FALSE(has_value);
    }
}


TEST(Optional, nullopt_constructor)
{
    using namespace hud;

    auto test = []() {
        Optional<HUD_TEST::NonBitwiseType> option(nullopt);
        return option.has_value();
    };

    // Non constant
    {
        ASSERT_FALSE(test());
    }

    // Constant
    {
        constexpr bool has_value = test();
        ASSERT_FALSE(has_value);
    }
}

TEST(Optional, constructor_in_place_of_non_trivially_constructible_type)
{
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyConstructibleV<Type>);

    auto test = []() {
        i32 destructor_counter = 0;
        Optional<Type> option(inplace, 123, &destructor_counter);
        return std::tuple{
            option.has_value(),
            option.value().id() == 123,
            option.value().destructor_counter() == &destructor_counter,
            *option.value().destructor_counter(),
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 0);
    }
}

TEST(Optional, constructor_in_place_of_trivially_constructible_type)
{
    using namespace hud;

    using Type = i32;
    static_assert(IsTriviallyConstructibleV<Type>);

    auto test = []() {
        i32 destructor_counter = 42;
        Optional<Type> option(inplace, destructor_counter);
        return std::tuple{
            option.has_value(),
            option.value() == 42
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}



TEST(Optional, copy_construct_bitwise_copy_constructible_same_type) {
    using namespace hud;

    using Type = i32;
    static_assert(IsBitwiseCopyConstructibleV<Type>);

    // If Type is bitwise copy constructible, Optional<Type> must be bitwise copy constructible
    static_assert(IsBitwiseCopyConstructibleV<Optional<Type>>);

    auto test = [](const Optional<Type>& copied) {
        Optional<Type> option(copied);
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value() == copied.value(),
            option.value(),
        };
    };

    // Non constant
    {

        const auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }
}

TEST(Optional, copy_construct_non_bitwise_copy_constructible_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsBitwiseCopyConstructibleV<Type>);

    // If Type is non bitwise copy constructible, Optional<Type> must be non bitwise copy constructible
    static_assert(!IsBitwiseCopyConstructibleV<Optional<Type>>);

    auto test = [](const Optional<Type>& copied) {
        Optional<Type> option(copied);
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value() == copied.value(),
            option.value().constructor_count(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_assign_count(),
            option.value().move_assign_count(),
        };
    };

    // Non constant
    {
        const auto result = test(Optional<Type>(nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(Optional<Type>(nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
    }
}

TEST(Optional, trivially_move_constructible_if_type_is_trivially_move_constructible) {
    using namespace hud;

    using Type = i32;

    ASSERT_TRUE(IsTriviallyMoveConstructibleV<Type>);
    ASSERT_TRUE(IsTriviallyMoveConstructibleV<Optional<Type>>);
}

TEST(Optional, not_trivially_move_constructible_if_type_is_not_trivially_move_constructible) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    ASSERT_FALSE(IsTriviallyMoveConstructibleV<Type>);
    ASSERT_FALSE(IsTriviallyMoveConstructibleV<Optional<Type>>);
}

TEST(Optional, move_construct_bitwise_copy_constructible_same_type) {
    using namespace hud;

    using Type = i32;
    static_assert(IsBitwiseCopyConstructibleV<Type>);
    static_assert(IsBitwiseMoveConstructibleV<Type>);

    // If Type is bitwise copy constructible, Optional<Type> must be bitwise copy constructible
    static_assert(IsBitwiseCopyConstructibleV<Optional<Type>>);
    static_assert(IsBitwiseMoveConstructibleV<Optional<Type>>);

    auto test = [](Optional<Type>&& copied) {
        Optional<Type> option(hud::move(copied));
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value() == copied.value(),
            option.value(),
        };
    };

    // Non constant
    {

        const auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }
}

TEST(Optional, move_construct_non_bitwise_copy_constructible_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;

    // Ensure the type is copyable but not moveable
    static_assert(!IsBitwiseMoveConstructibleV<Type>);
    static_assert(IsCopyConstructibleV<Type>);
    static_assert(!IsMoveConstructibleV<Type>);

    // If Type is copy constructible but not moveable, 
    // Optional<Type> is still move constructible but call the copy constructor of Type
    static_assert(!IsBitwiseCopyConstructibleV<Optional<Type>>);
    static_assert(IsMoveConstructibleV<Optional<Type>>);
    static_assert(IsCopyConstructibleV<Optional<Type>>);

    auto test = [](Optional<Type>&& copied) {
        Optional<Type> option(hud::move(copied));
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value().id() == copied.value().id(),
            option.value().copy_constructor_count(),
            option.value().id()
        };
    };

    // Non constant
    {
        const auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 123);

    }

    // Constant
    // MSVC call copy constructor instead of move constructor 
    // https://developercommunity.visualstudio.com/t/constexpr-stdconstruct-at-do-not-works/1545985
#if !defined(HD_COMPILER_MSVC)
    constexpr auto result = test(Optional<Type>(123));
    ASSERT_TRUE(std::get<0>(result));
    ASSERT_TRUE(std::get<1>(result));
    ASSERT_TRUE(std::get<2>(result));
    ASSERT_EQ(std::get<3>(result), 1u);
    ASSERT_EQ(std::get<4>(result), 123);
#endif

}

TEST(Optional, move_construct_bitwise_move_constructible_same_type) {
    using namespace hud;

    using Type = i32;
    static_assert(IsBitwiseMoveConstructibleV<Type>);

    // If Type is bitwise move constructible, Optional<Type> must be bitwise move constructible
    static_assert(IsBitwiseMoveConstructibleV<Optional<Type>>);

    auto test = [](Optional<Type>&& copied) {
        Optional<Type> option(hud::move(copied));
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value() == copied.value(),
            option.value(),
        };
    };

    // Non constant
    {

        const auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }

    // Constant
    {
        constexpr auto result = test(Optional<Type>(123));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 123);
    }
}

TEST(Optional, move_construct_non_bitwise_move_constructible_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsBitwiseMoveConstructibleV<Type>);

    // If Type is non bitwise copy constructible, Optional<Type> must be non bitwise copy constructible
    static_assert(!IsBitwiseMoveConstructibleV<Optional<Type>>);

    auto test = [](Optional<Type>&& copied) {
        Optional<Type> option(hud::move(copied));
        return std::tuple{
            option.has_value(),
            copied.has_value(),
            option.value().id() == copied.value().id(),
            option.value().constructor_count(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_assign_count(),
            option.value().move_assign_count()
        };
    };

    // Non constant
    {
        const auto result = test(Optional<Type>(inplace, 123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);

    }

    // Constant
    {
        constexpr auto result = test(Optional<Type>(inplace, 123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
    }
}

TEST(Optional, param_constructor_bitwise_copy_constructible_same_type_by_copy) {
    using namespace hud;

    using Type = i32;
    static_assert(IsBitwiseCopyConstructibleV<Type>);
    static_assert(IsCopyConstructibleV<Optional<Type>, Type>);
    static_assert(!IsBitwiseCopyConstructibleV<Optional<Type>, Type>);

    auto test = [](i32 value) {
        Optional<Type> option(value);
        return std::tuple{
           option.has_value(),
           option.value() == value
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}

TEST(Optional, param_constructor_non_bitwise_copy_constructible_same_type_by_copy) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsBitwiseCopyConstructibleV<Type>);
    static_assert(IsCopyConstructibleV<Optional<Type>, Type>);
    static_assert(!IsBitwiseCopyConstructibleV<Optional<Type>, Type>);

    auto test = [](const Type& value) {
        Optional<Type> option(value);
        return std::tuple{
            option.has_value(),
            option.value().id() == value.id(),
            option.value().constructor_count(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_assign_count(),
            option.value().move_assign_count()

        };
    };

    // Non constant
    {
        const auto result = test(Type(123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(Type(123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
    }
}


TEST(Optional, param_constructor_bitwise_move_constructible_same_type_by_move) {
    using namespace hud;

    using Type = i32;
    static_assert(IsBitwiseMoveConstructibleV<Type>);
    static_assert(IsMoveConstructibleV<Optional<Type>, Type>);
    static_assert(!IsBitwiseMoveConstructibleV<Optional<Type>, Type>);

    auto test = [](i32 value) {
        Optional<Type> option(hud::move(value));
        return std::tuple{
           option.has_value(),
           option.value() == value
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}

TEST(Optional, param_constructor_non_bitwise_move_constructible_same_type_by_move) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsBitwiseMoveConstructibleV<Type>);
    static_assert(IsMoveConstructibleV<Optional<Type>, Type>);
    static_assert(!IsBitwiseMoveConstructibleV<Optional<Type>, Type>);

    auto test = [](Type&& value) {
        Optional<Type> option(hud::move(value));
        return std::tuple{
            option.has_value(),
            option.value().id() == value.id(),
            option.value().constructor_count(),
            option.value().copy_constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_assign_count(),
            option.value().move_assign_count()

        };
    };

    // Non constant
    {
        const auto result = test(Type(123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(Type(123, nullptr));
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
    }
}

