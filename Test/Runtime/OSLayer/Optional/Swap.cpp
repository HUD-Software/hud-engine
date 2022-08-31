#include <OSLayer/Containers/Optional.h>


TEST(Optional, swap_empty_with_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2;
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
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

TEST(Optional, swap_empty_with_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2;
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
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

TEST(Optional, swap_empty_with_non_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2{ 123 };
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option.value(),
            option2.has_value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }
}

TEST(Optional, swap_empty_with_non_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2{ inplace, 123, nullptr };
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }
}

TEST(Optional, swap_non_empty_with_non_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option{ 456 };
        Optional<Type> option2{ 123 };
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option.value(),
            option2.has_value(),
            option2.value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, swap_non_empty_with_non_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option{ inplace, 456, nullptr };
        Optional<Type> option2{ inplace, 123, nullptr };
        option.swap(option2);
        return std::tuple{
            option.has_value(),
            option.value().id(),
            option2.has_value(),
            option2.value().id()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, hud_swap_empty_with_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2;
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
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

TEST(Optional, hud_swap_empty_with_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2;
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
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

TEST(Optional, hud_swap_empty_with_non_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2{ 123 };
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option.value(),
            option2.has_value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }
}

TEST(Optional, hud_swap_empty_with_non_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option;
        Optional<Type> option2{ inplace, 123, nullptr };
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option2.has_value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }
}

TEST(Optional, hud_swap_non_empty_with_non_empty_trivial_type) {
    using namespace hud;

    using Type = i32;

    const auto test = []() {
        Optional<Type> option{ 456 };
        Optional<Type> option2{ 123 };
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option.value(),
            option2.has_value(),
            option2.value()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, hud_swap_non_empty_with_non_empty_non_trivial_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    const auto test = []() {
        Optional<Type> option{ inplace, 456, nullptr };
        Optional<Type> option2{ inplace, 123, nullptr };
        hud::swap(option, option2);
        return std::tuple{
            option.has_value(),
            option.value().id(),
            option2.has_value(),
            option2.value().id()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}
