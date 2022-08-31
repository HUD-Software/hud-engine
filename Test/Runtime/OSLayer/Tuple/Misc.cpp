#include <OSLayer/Containers/Tuple.h>
#include <OSLayer/Traits/IsSame.h>
#include <Misc/NonBitwiseType.h>

TEST(Tuple, sizeof_is_correct) {
    ASSERT_EQ(sizeof(hud::Tuple<>), 1u);
    ASSERT_EQ(sizeof(hud::Tuple<i32>), 4u);
    ASSERT_EQ(sizeof(hud::Tuple<i32, i32>), 8u);
    ASSERT_EQ(sizeof(hud::Tuple<i32, i8, i32>), 12u);
}

TEST(Tuple, make_tuple) {
    auto tuple = hud::make_tuple(12, 15.0f, L'w');
    ASSERT_TRUE((hud::IsSameV<decltype(tuple), hud::Tuple<i32, f32, wchar>>));
    ASSERT_EQ(hud::get<0>(tuple), 12);
    ASSERT_EQ(hud::get<1>(tuple), 15.0f);
    ASSERT_EQ(hud::get<2>(tuple), L'w');

    const auto tuple2 = hud::make_tuple(12, 15.0f, L'w');
    ASSERT_TRUE((hud::IsSameV<decltype(tuple2), const hud::Tuple<i32, f32, wchar>>));
    ASSERT_EQ(hud::get<0>(tuple2), 12);
    ASSERT_EQ(hud::get<1>(tuple2), 15.0f);
    ASSERT_EQ(hud::get<2>(tuple2), L'w');

    constexpr auto tuple3 = hud::make_tuple(12, 15.0f, L'w');
    ASSERT_TRUE((hud::IsSameV<decltype(tuple3), const hud::Tuple<i32, f32, wchar>>));
    ASSERT_EQ(hud::get<0>(tuple3), 12);
    ASSERT_EQ(hud::get<1>(tuple3), 15.0f);
    ASSERT_EQ(hud::get<2>(tuple3), L'w');
}

TEST(Tuple, get) {
    const auto test = []() {
        auto tuple = hud::make_tuple(12, 15.0f, L'w');
        return std::tuple{
            hud::get<0>(tuple) == 12,
            hud::get<1>(tuple) == 15.0f,
            hud::get<2>(tuple) == L'w',
            hud::get<0>(move(tuple)) == 12,
            hud::get<1>(move(tuple)) == 15.0f,
            hud::get<2>(move(tuple)) == L'w'
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
    }

    // Constant
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


TEST(Tuple, tuple_cat) {
    using TupleType1 = hud::Tuple<i32, f32>;
    using TupleType2 = hud::Tuple<ansichar, wchar, char16, HUD_TEST::NonBitwiseType>;
    using TupleType3 = hud::Tuple<u64, f64, HUD_TEST::NonBitwiseType>;
    

    using CatType = decltype(hud::tuple_cat(TupleType1{}, TupleType2{}, TupleType3{}));

    CatType tuple = CatType{ 123, 12.0f, 'h', L'u', u'd', HUD_TEST::NonBitwiseType{456, nullptr}, 789u, 159., HUD_TEST::NonBitwiseType{753, nullptr} };

    ASSERT_EQ(hud::TupleSizeV<CatType>, hud::TupleSizeV<TupleType1> +hud::TupleSizeV<TupleType2> +hud::TupleSizeV<TupleType3>);
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple)), i32&>));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple)), f32& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(tuple)), ansichar& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<3>(tuple)), wchar& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<4>(tuple)), char16& >));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<5>(tuple)), HUD_TEST::NonBitwiseType& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<6>(tuple)), u64& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<7>(tuple)), f64& > ));
    ASSERT_TRUE((hud::IsSameV<decltype(hud::get<8>(tuple)), HUD_TEST::NonBitwiseType& > ));

    ASSERT_EQ(hud::get<0>(tuple), 123);
    ASSERT_EQ(hud::get<1>(tuple), 12.0f);
    ASSERT_EQ(hud::get<2>(tuple), 'h');
    ASSERT_EQ(hud::get<3>(tuple), L'u');
    ASSERT_TRUE(hud::get<4>(tuple) == u'd');
    ASSERT_EQ(hud::get<5>(tuple).id(), 456);
    ASSERT_EQ(hud::get<5>(tuple).destructor_counter(), nullptr);
    ASSERT_EQ(hud::get<5>(tuple).constructor_count(), 1u);
    ASSERT_EQ(hud::get<5>(tuple).copy_constructor_count(), 0u);
    ASSERT_EQ(hud::get<5>(tuple).move_constructor_count(), 1u);
    ASSERT_EQ(hud::get<5>(tuple).copy_assign_count(), 0u);
    ASSERT_EQ(hud::get<5>(tuple).move_assign_count(), 0u);
    ASSERT_EQ(hud::get<6>(tuple), 789u);
    ASSERT_EQ(hud::get<7>(tuple), 159.);
    ASSERT_EQ(hud::get<8>(tuple).id(), 753);
    ASSERT_EQ(hud::get<8>(tuple).destructor_counter(), nullptr);
    ASSERT_EQ(hud::get<8>(tuple).constructor_count(), 1u);
    ASSERT_EQ(hud::get<8>(tuple).copy_constructor_count(), 0u);
    ASSERT_EQ(hud::get<8>(tuple).move_constructor_count(), 1u);
    ASSERT_EQ(hud::get<8>(tuple).copy_assign_count(), 0u);
    ASSERT_EQ(hud::get<8>(tuple).move_assign_count(), 0u);

    using EmptyCatType = decltype(hud::tuple_cat());
    ASSERT_EQ(hud::TupleSizeV<EmptyCatType>, 0u);
}