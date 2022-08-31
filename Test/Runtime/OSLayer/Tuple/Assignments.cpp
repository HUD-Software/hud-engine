#include <OSLayer/Containers/Tuple.h>
#include <Misc/NonBitwiseCopyAssignableType.h>

TEST(Tuple, copy_assign_trivially_copy_assignable_same_types) {
    using TupleType = hud::Tuple<f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        const TupleType other_tuple{ 12.0f, 123, L'h' };
        tuple = other_tuple;
        return std::tuple{
            hud::get<0>(tuple) == 12.f,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, copy_assign_trivially_copy_assignable_different_types) {
    using TupleType = hud::Tuple<u64, i32, wchar>;
    using OtherTupleType = hud::Tuple<u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        const OtherTupleType other_tuple{ (u16)12, (i16)123, u'h' };
        tuple = other_tuple;
        return std::tuple{
            hud::get<0>(tuple) == 12,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, copy_assign_non_trivially_copy_assignable_same_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType ,f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        const TupleType other_tuple{ 1, 12.0f, 123, L'h' };
        tuple = other_tuple;
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));

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
    }
}

TEST(Tuple, copy_assign_non_trivially_copy_assignable_different_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType2, f32, i32, wchar>;
    using OtherTupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType, u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        const OtherTupleType other_tuple{ 1, (u16)12, (i16)123, u'h' };
        tuple = other_tuple;
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));

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
    }
}

TEST(Tuple, move_assign_trivially_copy_assignable_same_types) {
    using TupleType = hud::Tuple<f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        TupleType other_tuple{ 12.0f, 123, L'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple) == 12.f,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, move_assign_trivially_copy_assignable_different_types) {
    using TupleType = hud::Tuple<u64, i32, wchar>;
    using OtherTupleType = hud::Tuple<u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        OtherTupleType other_tuple{ (u16)12, (i16)123, u'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple) == 12,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, move_assign_non_trivially_copy_assignable_same_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType, f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        TupleType other_tuple{ 1, 12.0f, 123, L'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));

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
    }
}

TEST(Tuple, move_assign_non_trivially_copy_assignable_different_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType2, f32, i32, wchar>;
    using OtherTupleType = hud::Tuple<HUD_TEST::NonBitwiseCopyAssignableType, u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        OtherTupleType other_tuple{ 1, (u16)12, (i16)123, u'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));

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
    }
}

TEST(Tuple, move_assign_trivially_move_assignable_same_types) {
    using TupleType = hud::Tuple<f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        TupleType other_tuple{ 12.0f, 123, L'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple) == 12.f,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, move_assign_trivially_move_assignable_different_types) {
    using TupleType = hud::Tuple<u64, i32, wchar>;
    using OtherTupleType = hud::Tuple<u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        OtherTupleType other_tuple{ (u16)12, (i16)123, u'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple) == 12,
            hud::get<1>(tuple) == 123,
            hud::get<2>(tuple) == L'h',
        };
    };


    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));

    }

    // Non constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
    }
}

TEST(Tuple, move_assign_non_trivially_move_assignable_same_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType, f32, i32, wchar>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        TupleType other_tuple{ 1, 12.0f, 123, L'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 0u,
            hud::get<0>(tuple).move_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
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
    }
}

TEST(Tuple, move_assign_non_trivially_move_assignable_different_types) {
    using TupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType2, f32, i32, wchar>;
    using OtherTupleType = hud::Tuple<HUD_TEST::NonBitwiseMoveAssignableType, u16, i16, char16>;

    const auto test = []() {
        TupleType tuple{ hud::taginit };
        OtherTupleType other_tuple{ 1, (u16)12, (i16)123, u'h' };
        tuple = hud::move(other_tuple);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 0u,
            hud::get<0>(tuple).copy_assign_count() == 0u,
            hud::get<0>(tuple).move_assign_count() == 1u,
            hud::get<1>(tuple) == 12.f,
            hud::get<2>(tuple) == 123,
            hud::get<3>(tuple) == L'h',
        };
    };


    // Constant
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
    }
}