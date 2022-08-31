#include <OSLayer/Containers/Tuple.h>

TEST(Tuple, swap_non_trivially_copy_assignable_same_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType, f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple_a{ 1, 12.0f, 123, L'c' };
        TupleType tuple_b{ 2, 36.0f, 568, L'p' };
        hud::swap(tuple_a, tuple_b);
        return std::tuple{
            hud::get<0>(tuple_a).id() == 2,
            hud::get<0>(tuple_a).move_assign_count() == 1u,
            hud::get<0>(tuple_a).copy_assign_count() == 0u,
            hud::get<0>(tuple_a).move_constructor_count() == 0u,
            hud::get<0>(tuple_a).copy_constructor_count() == 0u,
            hud::get<1>(tuple_a) == 36.0f,
            hud::get<2>(tuple_a) == 568,
            hud::get<3>(tuple_a) == L'p',
            hud::get<0>(tuple_b).id() == 1,
            hud::get<0>(tuple_b).move_assign_count() == 1u,
            hud::get<0>(tuple_b).copy_assign_count() == 0u,
            hud::get<0>(tuple_b).move_constructor_count() == 1u,
            hud::get<0>(tuple_b).copy_constructor_count() == 0u,
            hud::get<1>(tuple_b) == 12.0f,
            hud::get<2>(tuple_b) == 123,
            hud::get<3>(tuple_b) == L'c',
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
    }


    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
    }
}

TEST(Tuple, swap_non_trivially_copy_assignable_different_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType2, f32, i32, wchar>;
    using OtherTupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType, f32, i32, wchar>;
    const auto test = []() {
        TupleType tuple_a{ 1, 12.0f, 123, L'c' };
        OtherTupleType tuple_b{ 2, 36.0f, 568, L'p' };
        hud::swap(tuple_a, tuple_b);
        return std::tuple{
            hud::get<0>(tuple_a).id() == 2,
            hud::get<0>(tuple_a).move_assign_count() == 1u,
            hud::get<0>(tuple_a).copy_assign_count() == 0u,
            hud::get<0>(tuple_a).move_constructor_count() == 0u,
            hud::get<0>(tuple_a).copy_constructor_count() == 0u,
            hud::get<1>(tuple_a) == 36.0f,
            hud::get<2>(tuple_a) == 568,
            hud::get<3>(tuple_a) == L'p',
            hud::get<0>(tuple_b).id() == 1,
            hud::get<0>(tuple_b).move_assign_count() == 1u,
            hud::get<0>(tuple_b).copy_assign_count() == 0u,
            hud::get<0>(tuple_b).move_constructor_count() == 1u,
            hud::get<0>(tuple_b).copy_constructor_count() == 0u,
            hud::get<1>(tuple_b) == 12.0f,
            hud::get<2>(tuple_b) == 123,
            hud::get<3>(tuple_b) == L'c',
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
    }


    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
    }
}
