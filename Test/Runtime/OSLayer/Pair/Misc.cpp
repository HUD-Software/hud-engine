#include <OSLayer/Containers/Pair.h>

#include <OSLayer/Traits/IsSame.h>

TEST(Pair, inner_is_correct) {
    using namespace hud;

    using PairType = Pair<i32, u32>;
    
    bool is_first_same = hud::IsSameV<PairType::FirstType, i32>;
    ASSERT_TRUE(is_first_same);

    bool is_second_same = hud::IsSameV<PairType::SecondType, u32>;
    ASSERT_TRUE(is_second_same);
}

TEST(Pair, sizeof_pair_is_sizeof_inner_types) {
    using namespace hud;

    using PairType = Pair<i32, u64>;
    struct shoud_be { i32 f; u64 s; };
    ASSERT_EQ(sizeof(PairType), sizeof(shoud_be) );
}

TEST(Pair, make_pair_create_pair_trivially_constructible) {
    using namespace hud;

    using Type = i32;
    static_assert(IsTriviallyConstructibleV<Type, Type&&>);

    const auto test = [](Type&& t1, Type&& t2) {
        const auto pair = make_pair(t1, t2);
        return std::tuple{
            pair.first,
            pair.second
        };
    };
    
    // Non constant
    {
        const auto result = test(123,456);

        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);

        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }
}

TEST(Pair, make_pair_create_pair_non_trivial) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    static_assert(IsConstructibleV<Type, Type&&>);
    static_assert(!IsTriviallyConstructibleV<Type, Type&&>);

    const auto test = [](Type&& t1, Type&& t2) {
        const auto pair = make_pair(forward<Type>(t1), forward<Type>(t2));
        return std::tuple{
            pair.first.id(),
            pair.first.move_assign_count(),
            pair.first.copy_assign_count(),
            pair.first.constructor_count(),
            pair.first.move_constructor_count(),
            pair.first.copy_constructor_count(),
            pair.second.id(),
            pair.second.move_assign_count(),
            pair.second.copy_assign_count(),
            pair.second.constructor_count(),
            pair.second.move_constructor_count(),
            pair.second.copy_constructor_count(),
        };
    };

    // Non constant
    {
        const auto result = test(Type{ 123, nullptr }, Type{ 456, nullptr });

        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 456);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(Type{ 123, nullptr }, Type{ 456, nullptr });

        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 456);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }
}

TEST(Pair, get_is_usable_with_pair) {
    using namespace hud;

    const auto test = [](i32 t1, i32 t2) {
        const auto pair = make_pair(t1, t2);
        return std::tuple{
            get<0>(pair),
            get<1>(pair)
        };
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456);
    }
}

TEST(Pair, TupleSize) {
    using namespace hud;

    constexpr usize tuple_size = TupleSizeV<Pair<u32, u64>>;
    ASSERT_EQ(tuple_size, 2u);
}

TEST(Pair, TupleElement) {
    using namespace hud;
    constexpr bool is_tuple_element_0_same = IsSameV<TupleElementT<0, Pair<u32, u64> >, u32>;
    constexpr bool is_tuple_element_1_same = IsSameV<TupleElementT<1, Pair<u32, u64> >, u64>;
    ASSERT_TRUE(is_tuple_element_0_same);
    ASSERT_TRUE(is_tuple_element_1_same);
}