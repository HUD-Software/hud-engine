#include <OSLayer/Containers/Pair.h>

TEST(Optional, swap_empty_trivial_type) {
    using namespace hud;

    // Pair::swap
    {


        const auto test = [](Pair<i32, wchar> a, Pair<i32, wchar> b) {
            static_assert(IsSwappableV<usize, usize>);
            a.swap(b);
            return std::tuple{
                a.first,
                a.second,
                b.first,
                b.second
            };
        };

        // Non constant
        {
            const auto result = test({ 1, L'a' }, { 2, L'b' });

            ASSERT_EQ(std::get<0>(result), 2);
            ASSERT_EQ(std::get<1>(result), L'b');
            ASSERT_EQ(std::get<2>(result), 1);
            ASSERT_EQ(std::get<3>(result), L'a');
        }

        // Constant
        {
            constexpr auto result = test({ 1, L'a' }, { 2, L'b' });

            ASSERT_EQ(std::get<0>(result), 2);
            ASSERT_EQ(std::get<1>(result), L'b');
            ASSERT_EQ(std::get<2>(result), 1);
            ASSERT_EQ(std::get<3>(result), L'a');
        }
    }

    // hud::swap
    {
        const auto test = [](Pair<i32, wchar> a, Pair<i32, wchar> b) {
            static_assert(IsSwappableV<usize, usize>);
            swap(a, b);
            return std::tuple{
                a.first,
                a.second,
                b.first,
                b.second
            };
        };

        // Non constant
        {
            const auto result = test({ 1, L'a' }, { 2, L'b' });

            ASSERT_EQ(std::get<0>(result), 2);
            ASSERT_EQ(std::get<1>(result), L'b');
            ASSERT_EQ(std::get<2>(result), 1);
            ASSERT_EQ(std::get<3>(result), L'a');
        }

        // Constant
        {
            constexpr auto result = test({ 1, L'a' }, { 2, L'b' });

            ASSERT_EQ(std::get<0>(result), 2);
            ASSERT_EQ(std::get<1>(result), L'b');
            ASSERT_EQ(std::get<2>(result), 1);
            ASSERT_EQ(std::get<3>(result), L'a');
        }
    }
}