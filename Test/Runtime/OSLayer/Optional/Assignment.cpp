#include <OSLayer/Containers/Optional.h>
#include <OSLayer/Traits/IsTriviallyCopyConstructible.h>
#include <OSLayer/Traits/IsTriviallyMoveConstructible.h>
#include <OSLayer/Traits/IsTriviallyCopyAssignable.h>
#include <OSLayer/Traits/IsTriviallyMoveAssignable.h>

#include <optional>

// Nullopt
TEST(Optional, assign_empty_trivial_type_with_nullopt) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = []() {
        Optional<Type> option;
        const bool had_value = option.has_value();

        option = nullopt;

        return std::tuple{
            had_value,
            option.has_value()
        };
    };

    // Non constant
    {
        auto result = test();
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

TEST(Optional, assign_empty_non_trivial_type_with_nullopt) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);

    const auto test = []() {
        Optional<Type> option;
        const bool had_value = option.has_value();

        option = nullopt;

        return std::tuple{
            had_value,
            option.has_value()
        };
    };

    // Non constant
    {
        auto result = test();
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

TEST(Optional, assign_non_empty_trivial_type_with_nullopt) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = [](Type value) {
        Optional<Type> option{ value };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = nullopt;

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),

        };
    };

    // Non constant
    {
        auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_FALSE(std::get<2>(result));
    }
}

TEST(Optional, assign_non_empty_non_trivial_type_with_nullopt) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);

    const auto test = []() {
        i32 destructor_count{ 0 };
        Optional<Type> option{ inplace, &destructor_count };
        const bool had_value_before = option.has_value();
        const i32 destructor_count_before = destructor_count;
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 constructor_count_before = option.value().constructor_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();

        option = nullopt;

        return std::tuple{
            had_value_before,
            destructor_count_before,
            move_assign_count_before,
            copy_assign_count_before,
            constructor_count_before,
            move_constructor_count_before,
            copy_constructor_count_before,
            option.has_value(),
            destructor_count
        };
    };

    // Non constant
    {
        auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_FALSE(std::get<7>(result));
        ASSERT_EQ(std::get<8>(result), 1);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_FALSE(std::get<7>(result));
        ASSERT_EQ(std::get<8>(result), 1);
    }
}

TEST(Optional, assign_by_copy_empty_trivially_copy_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = value;

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_copy_empty_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const OtherType value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = value;

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_copy_non_empty_trivially_copy_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const Type before, const Type after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = after;

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123,456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);

    }

    // Constant
    {
        constexpr auto result = test(123,456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Optional, assign_by_copy_non_empty_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const Type before, const OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = after;

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_copy_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const i32 value) {
        i32 destructor_count;
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        const Type other{ value, &destructor_count };
        option = other;

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value().id(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
        ASSERT_EQ(std::get<8>(result), 0);
        
    }

    // Constant
   /* {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
        ASSERT_EQ(std::get<8>(result), 0);
    }*/
}

TEST(Optional, assign_by_copy_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const OtherType other{ value };
        option = other;

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_copy_non_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        i32 destructor_count;
        i32 other_destructor_count;
        Optional<Type> option{ inplace, before, &destructor_count };

        const bool has_value_before = option.has_value();
        const i32 id_before = option.value().id();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 constructor_count_before = option.value().constructor_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const i32 destructor_count_before = destructor_count;

        const Type other{ after, &other_destructor_count };
        option = other;

        return std::tuple{
            has_value_before,
            id_before,
            move_assign_count_before,
            copy_assign_count_before,
            constructor_count_before,
            move_constructor_count_before,
            copy_constructor_count_before,
            destructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count,
            other_destructor_count,
        };
        
    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 1u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 1u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }
}

TEST(Optional, assign_by_copy_non_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;


    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();

        const OtherType other{ after };

        option = other;

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_empty_trivially_copy_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](Type value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = hud::move(value);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_move_empty_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](OtherType value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = hud::move(value);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_move_non_empty_trivially_copy_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const Type before, Type after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = hud::move(after);

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_non_empty_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const Type before, OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = hud::move(after);

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_empty_non_trivially_copy_assignable_same_type) {
    // Current STD specification make it not possible
    // because IsConstructibleV<T, U> where T and U is not move assignable is false
    
    //using namespace hud;

    //using Type = HUD_TEST::NonBitwiseCopyAssignableType;

    //static_assert(!IsTriviallyCopyConstructibleV<Type>);
    //static_assert(!IsTriviallyCopyAssignableV<Type>);

    //const auto test = [](const i32 value) {
    //    Optional<Type> option;
    //    const bool had_value_before = option.has_value();

    //    Type other{ value };

    //    option = hud::move(other);

    //    return std::tuple{
    //        had_value_before,
    //        option.has_value(),
    //        option.value().id(),
    //        option.value().copy_assign_count(),
    //        option.value().copy_constructor_count(),
    //    };
    //};


    //// Non constant
    //{
    //    auto result = test(123);
    //    ASSERT_FALSE(std::get<0>(result));
    //    ASSERT_TRUE(std::get<1>(result));
    //    ASSERT_EQ(std::get<2>(result), 123);
    //    ASSERT_EQ(std::get<3>(result), 0u);
    //    ASSERT_EQ(std::get<4>(result), 1u);
    //}

    //// Constant
    //{
    //    auto result = test(123);
    //    ASSERT_FALSE(std::get<0>(result));
    //    ASSERT_TRUE(std::get<1>(result));
    //    ASSERT_EQ(std::get<2>(result), 123);
    //    ASSERT_EQ(std::get<3>(result), 0u);
    //    ASSERT_EQ(std::get<4>(result), 1u);
    //}
}

TEST(Optional, assign_by_move_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        OtherType other{ value };
        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_move_non_empty_non_trivially_copy_assignable_same_type) {
    // Current STD specification make it not possible
    // because IsConstructibleV<T, U> where T and U is not move assignable is false
  
    //using namespace hud;
    //using Type = HUD_TEST::NonBitwiseCopyAssignableType;

    //static_assert(!IsTriviallyCopyConstructibleV<Type>);
    //static_assert(!IsTriviallyCopyAssignableV<Type>);

    //const auto test = [](const i32 before, const i32 after) {
    //    Optional<Type> option{ inplace, before };

    //    const bool has_value_before = option.has_value();
    //    const i32 id_before = option.value().id();
    //    const u32 copy_assign_count_before = option.value().copy_assign_count();
    //    const u32 copy_constructor_count_before = option.value().copy_constructor_count();

    //    Type other{ after };
    //    option = hud::move(other);

    //    return std::tuple{
    //        has_value_before,
    //        id_before,
    //        copy_assign_count_before,
    //        copy_constructor_count_before,
    //        option.has_value(),
    //        option.value().id(),
    //        option.value().copy_assign_count(),
    //        option.value().copy_constructor_count(),
    //    };

    //};

    //// Non constant
    //{
    //    auto result = test(123, 456);
    //    ASSERT_TRUE(std::get<0>(result));
    //    ASSERT_EQ(std::get<1>(result), 123);
    //    ASSERT_EQ(std::get<2>(result), 0u);
    //    ASSERT_EQ(std::get<3>(result), 0u);
    //    ASSERT_TRUE(std::get<4>(result));
    //    ASSERT_EQ(std::get<5>(result), 456);
    //    ASSERT_EQ(std::get<6>(result), 1u);
    //    ASSERT_EQ(std::get<7>(result), 0u);
    //}

    //// Constant
    //{
    //    constexpr auto result = test(123, 456);
    //    ASSERT_TRUE(std::get<0>(result));
    //    ASSERT_EQ(std::get<1>(result), 123);
    //    ASSERT_EQ(std::get<2>(result), 0u);
    //    ASSERT_EQ(std::get<3>(result), 0u);
    //    ASSERT_TRUE(std::get<4>(result));
    //    ASSERT_EQ(std::get<5>(result), 456);
    //    ASSERT_EQ(std::get<6>(result), 1u);
    //    ASSERT_EQ(std::get<7>(result), 0u);
    //}
}

TEST(Optional, assign_by_move_non_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;


    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();

        OtherType other{ after };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_empty_trivially_move_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = []( Type value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = hud::move(value);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_move_empty_trivially_move_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](OtherType value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        option = hud::move(value);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, assign_by_move_non_empty_trivially_move_assignable_same_type) {
    using namespace hud;
    using Type = i32;
    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const Type before, Type after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = hud::move(after);

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_non_empty_trivially_move_assignable_different_type) {
    using namespace hud;
    using Type = i32;
    using OtherType = i16;
    static_assert(IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const Type before, OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        option = hud::move(after);

        return std::tuple{
            had_value_before,
            value_before,
            option.has_value(),
            option.value()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, assign_by_move_empty_non_trivially_move_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        Type other{ value };

        option = hud::move(other);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count(),
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }

    // Constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }
}

TEST(Optional, assign_by_move_empty_non_trivially_move_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        OtherType other{ value };
        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count(),
        };
    };

    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }
}

TEST(Optional, assign_by_move_non_empty_non_trivially_move_assignable_same_type) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ inplace, before };

        const bool has_value_before = option.has_value();
        const i32 id_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();

        Type other{ after };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            id_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            move_assign_count_before,
            move_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count(),
        };

    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);

    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }
}

TEST(Optional, assign_by_move_non_empty_non_trivially_move_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseMoveAssignableType;


    static_assert(!IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();

        OtherType other{ after };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            move_assign_count_before,
            move_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count(),
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);

    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }
}

TEST(Optional, copy_assign_empty_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);


    const auto test = [](const Type value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const Optional<Type> other{ value };

        option = other;

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, copy_assign_empty_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const OtherType value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const Optional<OtherType> other{ value };

        option = other;

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, copy_assign_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);


    const auto test = [](const i32 value) {
        i32 destructor_count_other{ 0 };
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const Optional<Type> other{ inplace, value,  &destructor_count_other };

        option = other;

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count_other
        };
    };

    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
        ASSERT_EQ(std::get<8>(result), 0);
    }


    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 1u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 1u);
        ASSERT_EQ(std::get<8>(result), 0);
    }

}

TEST(Optional, copy_assign_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        const Optional<OtherType> other{ value };

        option = other;

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
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

TEST(Optional, copy_assign_non_empty_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const Type before, const Type after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        const Optional<Type> other{ after };
        option = other;
        return std::tuple{
            had_value_before,
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

TEST(Optional, copy_assign_non_empty_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const Type before, const OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        const Optional<OtherType> other{ after };
        option = other;
        return std::tuple{
            had_value_before,
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

TEST(Optional, copy_assign_non_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        i32 destructor_count;
        i32 other_destructor_count;
        Optional<Type> option{ inplace, before, &destructor_count };

        const bool has_value_before = option.has_value();
        const i32 id_before = option.value().id();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 constructor_count_before = option.value().constructor_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const i32 destructor_count_before = destructor_count;

        const Optional<Type> other{ inplace, after,  &other_destructor_count };
        option = other;

        return std::tuple{
            has_value_before,
            id_before,
            move_assign_count_before,
            copy_assign_count_before,
            constructor_count_before,
            move_constructor_count_before,
            copy_constructor_count_before,
            destructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count,
            other_destructor_count,
        };

    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 1u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 1u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }
}

TEST(Optional, copy_assign_non_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();

        const Optional<OtherType> other{ after };

        option = other;

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, move_assign_empty_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const Optional<Type> other{ value };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, move_assign_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        const Optional<Type> other{ inplace, value};

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
        };
    };

    // Non constant
    {
        auto result = test(123);
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

TEST(Optional, move_assign_empty_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const OtherType value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        Optional<OtherType> other{ value };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, move_assign_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        const Optional<OtherType> other{ value };

        option = hud::move(other);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
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

TEST(Optional, move_assign_empty_trivially_move_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const Type value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        Optional<Type> other{ value };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, move_assign_empty_non_trivially_move_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        Optional<Type> other{ inplace, value };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count(),
        };
    };

    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }


    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }
}

TEST(Optional, move_assign_empty_trivially_move_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const OtherType value) {
        Optional<Type> option;
        const bool has_value_before = option.has_value();

        Optional<OtherType> other{ value };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            option.has_value(),
            option.value()
        };
    };


    // Non constant
    {
        auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }

    // Non constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
    }
}

TEST(Optional, move_assign_empty_non_trivially_move_assignable_different_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseMoveAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type>);
    static_assert(!IsTriviallyMoveAssignableV<Type>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 value) {
        Optional<Type> option;
        const bool had_value_before = option.has_value();

        Optional<OtherType> other{ value };

        option = hud::move(other);

        return std::tuple{
            had_value_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count()
        };
    };

    // Non constant
    {
        const auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }

    // Constant
    {
        constexpr auto result = test(123);
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 1u);
    }
}

TEST(Optional, move_assign_non_empty_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsTriviallyCopyAssignableV<Type>);

    Optional<Type> option{ 123 };
    ASSERT_TRUE(option.has_value());
    ASSERT_EQ(option.value(), 123);

    Optional<Type> other{ 456 };
    option = hud::move(other);

    ASSERT_TRUE(option.has_value());
    ASSERT_EQ(option.value(), 456);
}

TEST(Optional, move_assign_non_empty_non_trivially_copy_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseCopyAssignableType;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    Optional<Type> option{ 123 };
    ASSERT_TRUE(option.has_value());
    ASSERT_EQ(option.value().id(), 123);
    ASSERT_EQ(option.value().copy_assign_count(), 0u);
    ASSERT_EQ(option.value().copy_constructor_count(), 0u);

    Optional<Type> other{ 456 };
    option = hud::move(other);

    ASSERT_TRUE(option.has_value());
    ASSERT_EQ(option.value().id(), 456);
    ASSERT_EQ(option.value().copy_assign_count(), 1u);
    ASSERT_EQ(option.value().copy_constructor_count(), 0u);
}

TEST(Optional, move_assign_non_empty_trivially_copy_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const Type before, const OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        Optional<OtherType> other{ after };

        option = hud::move(other);

        return std::tuple{
            had_value_before,
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

TEST(Optional, move_assign_non_empty_non_trivially_copy_assignable_different_type) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseCopyAssignableType;

    static_assert(!IsTriviallyCopyConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyCopyAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();

        Optional<OtherType> other{ after };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
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

TEST(Optional, move_assign_non_empty_trivially_move_assignable_same_type) {
    using namespace hud;

    using Type = i32;

    static_assert(IsTriviallyMoveConstructibleV<Type>);
    static_assert(IsTriviallyMoveAssignableV<Type>);

    const auto test = [](const Type before, const Type after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        Optional<Type> other{ after };

        option = hud::move(other);

        return std::tuple{
            had_value_before,
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

TEST(Optional, move_assign_non_empty_non_trivially_move_assignable_same_type) {
    using namespace hud;

    using Type = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(!IsTriviallyCopyAssignableV<Type>);

    const auto test = [](const i32 before, const i32 after) {
        i32 destructor_count;
        i32 other_destructor_count;
        Optional<Type> option{ inplace, before, &destructor_count };

        const bool has_value_before = option.has_value();
        const i32 id_before = option.value().id();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 constructor_count_before = option.value().constructor_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const i32 destructor_count_before = destructor_count;

        Optional<Type> other{ inplace, after,  &other_destructor_count };
        option = hud::move(other);

        return std::tuple{
            has_value_before,
            id_before,
            move_assign_count_before,
            copy_assign_count_before,
            constructor_count_before,
            move_constructor_count_before,
            copy_constructor_count_before,
            destructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().move_assign_count(),
            option.value().copy_assign_count(),
            option.value().constructor_count(),
            option.value().move_constructor_count(),
            option.value().copy_constructor_count(),
            destructor_count,
            other_destructor_count,
        };

    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0);
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_EQ(std::get<9>(result), 456);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
        ASSERT_EQ(std::get<12>(result), 1u);
        ASSERT_EQ(std::get<13>(result), 0u);
        ASSERT_EQ(std::get<14>(result), 0u);
        ASSERT_EQ(std::get<15>(result), 0);
        ASSERT_EQ(std::get<16>(result), 0);
    }
}

TEST(Optional, move_assign_non_empty_trivially_move_assignable_different_type) {
    using namespace hud;

    using Type = i32;
    using OtherType = i16;

    static_assert(IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);


    const auto test = [](const Type before, const OtherType after) {
        Optional<Type> option{ before };
        const bool had_value_before = option.has_value();
        const Type value_before = option.value();

        Optional<OtherType> other{ after };
        option = hud::move(other);
        return std::tuple{
            had_value_before,
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

TEST(Optional, move_assign_non_empty_non_trivially_move_assignable_different_type) {
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveAssignableType2;
    using OtherType = HUD_TEST::NonBitwiseMoveAssignableType;

    static_assert(!IsTriviallyMoveConstructibleV<Type, OtherType>);
    static_assert(!IsTriviallyMoveAssignableV<Type, OtherType>);
    static_assert(IsNotSameV<Type, OtherType>);

    const auto test = [](const i32 before, const i32 after) {
        Optional<Type> option{ before };
        const bool has_value_before = option.has_value();
        const i32 value_before = option.value().id();
        const u32 copy_assign_count_before = option.value().copy_assign_count();
        const u32 copy_constructor_count_before = option.value().copy_constructor_count();
        const u32 move_assign_count_before = option.value().move_assign_count();
        const u32 move_constructor_count_before = option.value().move_constructor_count();

        Optional<OtherType> other{ after };

        option = hud::move(other);

        return std::tuple{
            has_value_before,
            value_before,
            copy_assign_count_before,
            copy_constructor_count_before,
            move_assign_count_before,
            move_constructor_count_before,
            option.has_value(),
            option.value().id(),
            option.value().copy_assign_count(),
            option.value().copy_constructor_count(),
            option.value().move_assign_count(),
            option.value().move_constructor_count()
        };
    };

    // Non constant
    {
        auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0u);
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_EQ(std::get<7>(result), 456);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 0u);
    }
}