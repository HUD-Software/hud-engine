#include <OSLayer/Containers/Tuple.h>

#include <OSLayer/Containers/Pair.h>

#include <OSLayer/Traits/IsSame.h>
#include <OSLayer/Traits/IsExplicitlyConstructible.h>
#include <OSLayer/Traits/IsImplicitlyConstructible.h>
#include <OSLayer/Traits/IsExplicitlyCopyConstructible.h>
#include <OSLayer/Traits/IsImplicitlyCopyConstructible.h>
#include <OSLayer/Traits/IsExplicitlyMoveConstructible.h>
#include <OSLayer/Traits/IsImplicitlyMoveConstructible.h>

#include <Misc/DefaultConstructibleType.h>
#include <Misc/NonBitwiseCopyConstructibleType.h>

#include <math.h> // isnan

namespace {
    struct ExplicitDefaultConstructible
        : public HUD_TEST::DefaultConstructibleType
    {
        constexpr explicit ExplicitDefaultConstructible() noexcept
            : HUD_TEST::DefaultConstructibleType() {
        }
    };
    static_assert(hud::IsExplicitlyDefaultConstructibleV<ExplicitDefaultConstructible>);

    struct ImplicitDefaultConstructible
        : public HUD_TEST::DefaultConstructibleType
    {
        constexpr ImplicitDefaultConstructible() noexcept
            : HUD_TEST::DefaultConstructibleType() {
        }
    };

    static_assert(hud::IsImplicitlyDefaultConstructibleV<ImplicitDefaultConstructible>);

    struct ExplicitlyCopyConstructible
        : public HUD_TEST::NonBitwiseCopyConstructibleType {

        constexpr ExplicitlyCopyConstructible(i32 id) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType(id) {
        }

        explicit constexpr ExplicitlyCopyConstructible(const ExplicitlyCopyConstructible& other) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType(other) {
        }
    };
    
    static_assert(hud::IsExplicitlyCopyConstructibleV<ExplicitlyCopyConstructible>);

    struct ExplicitlyCopyConstructible2
        : public HUD_TEST::NonBitwiseCopyConstructibleType2 {

        constexpr ExplicitlyCopyConstructible2(i32 id) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType2(id) {
        }

        explicit constexpr ExplicitlyCopyConstructible2(const ExplicitlyCopyConstructible& other) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType2(other) {
        }
    };
    static_assert(hud::IsExplicitlyCopyConstructibleV<ExplicitlyCopyConstructible2, ExplicitlyCopyConstructible>);

    struct ImplicitlyCopyConstructible
        : public HUD_TEST::NonBitwiseCopyConstructibleType {

        constexpr ImplicitlyCopyConstructible(i32 id) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType(id) {
        }

        constexpr ImplicitlyCopyConstructible(const ImplicitlyCopyConstructible& other) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType(other) {
        }
    };
    static_assert(hud::IsImplicitlyCopyConstructibleV<ImplicitlyCopyConstructible>);

    struct ImplicitlyCopyConstructible2
        : public HUD_TEST::NonBitwiseCopyConstructibleType2 {

        constexpr ImplicitlyCopyConstructible2(i32 id) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType2(id) {
        }

        constexpr ImplicitlyCopyConstructible2(const ImplicitlyCopyConstructible& other) noexcept
            : HUD_TEST::NonBitwiseCopyConstructibleType2(other) {
        }
    };
    static_assert(hud::IsImplicitlyCopyConstructibleV<ImplicitlyCopyConstructible2, ImplicitlyCopyConstructible>);

    struct ExplicitlyMoveConstructible
        : public HUD_TEST::NonBitwiseMoveConstructibleType {

        constexpr ExplicitlyMoveConstructible(i32 id) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(id) {
        }

        explicit constexpr ExplicitlyMoveConstructible(const ExplicitlyMoveConstructible& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(other) {
        }

        explicit constexpr ExplicitlyMoveConstructible(ExplicitlyMoveConstructible&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(hud::move(other)) {
        }
    };
    static_assert(hud::IsExplicitlyMoveConstructibleV<ExplicitlyMoveConstructible>);

    struct ExplicitlyMoveConstructible2
        : public HUD_TEST::NonBitwiseMoveConstructibleType2 {

        constexpr ExplicitlyMoveConstructible2(i32 id) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(id) {
        }

        explicit constexpr ExplicitlyMoveConstructible2(const ExplicitlyMoveConstructible& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(other) {
        }

        explicit constexpr ExplicitlyMoveConstructible2(ExplicitlyMoveConstructible&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(hud::move(other)) {
        }
    };
    static_assert(hud::IsExplicitlyMoveConstructibleV<ExplicitlyMoveConstructible2, ExplicitlyMoveConstructible>);

    struct ImplicitlyMoveConstructible
        : public HUD_TEST::NonBitwiseMoveConstructibleType {

        constexpr ImplicitlyMoveConstructible(i32 id) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(id) {
        }

        constexpr ImplicitlyMoveConstructible(const ImplicitlyMoveConstructible& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(other) {
        }

        constexpr ImplicitlyMoveConstructible(ImplicitlyMoveConstructible&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType(hud::move(other)) {
        }
    };

    static_assert(hud::IsImplicitlyMoveConstructibleV<ImplicitlyMoveConstructible>);

    struct ImplicitlyMoveConstructible2
        : public HUD_TEST::NonBitwiseMoveConstructibleType2 {

        constexpr ImplicitlyMoveConstructible2(i32 id) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(id) {
        }

        constexpr ImplicitlyMoveConstructible2(const ImplicitlyMoveConstructible& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(other) {
        }

        constexpr ImplicitlyMoveConstructible2(ImplicitlyMoveConstructible&& other) noexcept
            : HUD_TEST::NonBitwiseMoveConstructibleType2(hud::move(other)) {
        }
    };
    static_assert(hud::IsImplicitlyMoveConstructibleV<ImplicitlyMoveConstructible2, ImplicitlyMoveConstructible>);
}


TEST(Tuple, default_constructor_uninit) {
    using TupleType = hud::Tuple<>;
    using TupleType2 = hud::Tuple<i32, i32, i32>;
    using TupleType3 = hud::Tuple<i32, f32, wchar>;
    using TupleType4 = hud::Tuple<ExplicitDefaultConstructible, ImplicitDefaultConstructible>;
    using TupleType5 = hud::Tuple<ExplicitDefaultConstructible, i32>;

    ASSERT_EQ(hud::TupleSizeV<TupleType>, 0u);
    ASSERT_EQ(hud::TupleSizeV<TupleType2>, 3u);
    ASSERT_EQ(hud::TupleSizeV<TupleType3>, 3u);
    ASSERT_EQ(hud::TupleSizeV<TupleType4>, 2u);
    ASSERT_EQ(hud::TupleSizeV<TupleType5>, 2u);

    // Non constant
    {
        [[maybe_unused]] TupleType tuple1;

        TupleType2* tuple2 = hud::Memory::allocate_array<TupleType2>(1);
        hud::Memory::set(tuple2, sizeof(TupleType2), 0xFF);
        hud::Memory::construct_at(tuple2);
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(*tuple2)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(*tuple2)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(*tuple2)), i32&>));
        ASSERT_NE((hud::get<0>(*tuple2)), i32{});
        ASSERT_NE((hud::get<1>(*tuple2)), i32{});
        ASSERT_NE((hud::get<2>(*tuple2)), i32{});
        hud::Memory::destroy_array(tuple2, 1);
        hud::Memory::free(tuple2);

        TupleType3* tuple3 = hud::Memory::allocate_array<TupleType3>(1);
        hud::Memory::set(tuple3, sizeof(TupleType3), 0xFF);
        hud::Memory::construct_at(tuple3);
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(*tuple3)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(*tuple3)), f32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(*tuple3)), wchar&>));
        ASSERT_NE((hud::get<0>(*tuple3)), i32{});

        // Is nan always return false with clang in release with fast math enabled
        // See: https://clang.llvm.org/docs/UsersManual.html#cmdoption-ffast-math
        #if defined(HD_COMPILER_CLANG) && defined(HD_RELEASE) && defined(__FAST_MATH__)
        ASSERT_FALSE(isnan(hud::get<1>(*tuple3)));
        #else
        ASSERT_TRUE(isnan(hud::get<1>(*tuple3)));
        #endif
        ASSERT_NE((hud::get<2>(*tuple3)), wchar{});
        hud::Memory::destroy_array(tuple3, 1);
        hud::Memory::free(tuple3);

        TupleType4* tuple4 = hud::Memory::allocate_array<TupleType4>(1);
        hud::Memory::set(tuple4, sizeof(TupleType4), 0xFF);
        hud::Memory::construct_at(tuple4);
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(*tuple4)), ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(*tuple4)), ImplicitDefaultConstructible&>));
        ASSERT_EQ((hud::get<0>(*tuple4).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(*tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(*tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(*tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(*tuple4).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(*tuple4).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(*tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(*tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(*tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(*tuple4).move_constructor_count()), 0u);
        hud::Memory::destroy_array(tuple4, 1);
        hud::Memory::free(tuple4);

        TupleType5* tuple5 = hud::Memory::allocate_array<TupleType5>(1);
        hud::Memory::set(tuple5, sizeof(TupleType5), 0xFF);
        hud::Memory::construct_at(tuple5);
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(*tuple5)), ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(*tuple5)), i32&>));
        ASSERT_EQ((hud::get<0>(*tuple5).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(*tuple5).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(*tuple5).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(*tuple5).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(*tuple5).move_constructor_count()), 0u);
        ASSERT_NE(hud::get<1>(*tuple5), i32{});
        hud::Memory::destroy_array(tuple5, 1);
        hud::Memory::free(tuple5);

    }

    // Constant
    // Non empty uninit constexpr tuple is not possible because constexpr need initialized value
    {
        [[maybe_unused]] constexpr TupleType tuple;
        ASSERT_EQ(hud::TupleSizeV<TupleType>, 0u);
    }
}

TEST(Tuple, default_constructor_init) {
    using TupleType = hud::Tuple<>;
    using TupleType2 = hud::Tuple<i32, i32, i32>;
    using TupleType3 = hud::Tuple<i32, f32, wchar>;
    using TupleType4 = hud::Tuple<ExplicitDefaultConstructible, ImplicitDefaultConstructible>;
    using TupleType5 = hud::Tuple<ExplicitDefaultConstructible, i32>;

    ASSERT_EQ(hud::TupleSizeV<TupleType>, 0u);
    ASSERT_EQ(hud::TupleSizeV<TupleType2>, 3u);
    ASSERT_EQ(hud::TupleSizeV<TupleType3>, 3u);
    ASSERT_EQ(hud::TupleSizeV<TupleType4>, 2u);
    ASSERT_EQ(hud::TupleSizeV<TupleType5>, 2u);

    // Non constant
    {
        // No init for empty tuple
        [[maybe_unused]] TupleType tuple1;

        TupleType2 tuple2{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple2)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple2)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(tuple2)), i32&>));
        ASSERT_EQ((hud::get<0>(tuple2)), i32{});
        ASSERT_EQ((hud::get<1>(tuple2)), i32{});
        ASSERT_EQ((hud::get<2>(tuple2)), i32{});

        TupleType3 tuple3{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple3)), i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple3)), f32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(tuple3)), wchar&>));
        ASSERT_EQ((hud::get<0>(tuple3)), i32{});
        ASSERT_EQ((hud::get<1>(tuple3)), f32{});
        ASSERT_EQ((hud::get<2>(tuple3)), wchar{});

        TupleType4 tuple4{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple4)), ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple4)), ImplicitDefaultConstructible&>));
        ASSERT_EQ((hud::get<0>(tuple4).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple4).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).move_constructor_count()), 0u);

        TupleType5 tuple5{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple5)), ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple5)), i32&>));
        ASSERT_EQ((hud::get<0>(tuple5).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple5).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple5).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple5).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple5).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple5)), i32{});
    }

    // Constant
    {
        [[maybe_unused]] constexpr TupleType tuple1;

        constexpr TupleType2 tuple2{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple2)), const i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple2)), const i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(tuple2)), const i32&>));

        ASSERT_EQ((hud::get<0>(tuple2)), i32{});
        ASSERT_EQ((hud::get<1>(tuple2)), i32{});
        ASSERT_EQ((hud::get<2>(tuple2)), i32{});

        constexpr TupleType3 tuple3{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple3)), const i32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple3)), const f32&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<2>(tuple3)), const wchar&>));

        ASSERT_EQ((hud::get<0>(tuple3)), i32{});
        ASSERT_EQ((hud::get<1>(tuple3)), f32{});
        ASSERT_EQ((hud::get<2>(tuple3)), wchar{});

        constexpr TupleType4 tuple4{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple4)), const ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple4)), const ImplicitDefaultConstructible&>));
        ASSERT_EQ((hud::get<0>(tuple4).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple4).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple4).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple4).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple4).move_constructor_count()), 0u);

        constexpr TupleType5 tuple5{ hud::taginit };
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<0>(tuple5)), const ExplicitDefaultConstructible&>));
        ASSERT_TRUE((hud::IsSameV<decltype(hud::get<1>(tuple5)), const i32&>));
        ASSERT_EQ((hud::get<0>(tuple5).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple5).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple5).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple5).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple5).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple5)), i32{});
    }
}

TEST(Tuple, default_constructor_explicit_types) {
    using TupleType = hud::Tuple<ExplicitDefaultConstructible, ExplicitDefaultConstructible>;

    ASSERT_TRUE(hud::IsExplicitlyDefaultConstructibleV<TupleType>);

    // Non constant
    {
        // No init for empty tuple
        TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }

    // Constant
    {
        // No init for empty tuple
        constexpr TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }
}

TEST(Tuple, default_constructor_implicit_types) {
    using TupleType = hud::Tuple<ImplicitDefaultConstructible, ImplicitDefaultConstructible>;

    ASSERT_TRUE(hud::IsImplicitlyDefaultConstructibleV<TupleType>);

    // Non constant
    {
        // No init for empty tuple
        TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }

    // Constant
    {
        // No init for empty tuple
        constexpr TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }
}

TEST(Tuple, default_constructor_mix_implicit_explicit_types) {
    using TupleType = hud::Tuple<ImplicitDefaultConstructible, ExplicitDefaultConstructible>;

    ASSERT_TRUE(hud::IsExplicitlyDefaultConstructibleV<TupleType>);

    // Non constant
    {
        // No init for empty tuple
        TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }

    // Constant
    {
        // No init for empty tuple
        constexpr TupleType tuple;

        ASSERT_EQ((hud::get<0>(tuple).id()), ImplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<0>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<0>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<0>(tuple).move_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).id()), ExplicitDefaultConstructible::DEFAULT_ID_VALUE);
        ASSERT_EQ((hud::get<1>(tuple).default_constructor_count()), 1u);
        ASSERT_EQ((hud::get<1>(tuple).constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).copy_constructor_count()), 0u);
        ASSERT_EQ((hud::get<1>(tuple).move_constructor_count()), 0u);
    }
}

TEST(Tuple, default_constructor_is_explicit_if_at_least_one_type_is_explicitly_default_constructible) {
    ASSERT_FALSE(hud::IsExplicitlyDefaultConstructibleV<hud::Tuple<>>);
    ASSERT_FALSE((hud::IsExplicitlyDefaultConstructibleV<hud::Tuple<i32, f32, wchar>>));
    ASSERT_FALSE((hud::IsExplicitlyDefaultConstructibleV<hud::Tuple<ImplicitDefaultConstructible, ImplicitDefaultConstructible>>));
    ASSERT_TRUE((hud::IsExplicitlyDefaultConstructibleV<hud::Tuple<ImplicitDefaultConstructible, ExplicitDefaultConstructible>>));
    ASSERT_TRUE((hud::IsExplicitlyDefaultConstructibleV<hud::Tuple<ExplicitDefaultConstructible, ExplicitDefaultConstructible>>));
}

TEST(Tuple, constructor_by_copy_explicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyCopyConstructible&, const ExplicitlyCopyConstructible&>));
    
    const auto test = []() {
        const ExplicitlyCopyConstructible obj1(1);
        const ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_copy_explicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyCopyConstructible&, const ExplicitlyCopyConstructible&>));

    const auto test = []() {
        const ExplicitlyCopyConstructible obj1(1);
        const ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_copy_implicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, const ImplicitlyCopyConstructible&, const ImplicitlyCopyConstructible&>));

    const auto test = []() {
        const ImplicitlyCopyConstructible obj1(1);
        const ImplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_copy_implicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, const ImplicitlyCopyConstructible&, const ImplicitlyCopyConstructible&>));

    const auto test = []() {
        const ImplicitlyCopyConstructible obj1(1);
        const ImplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_copy_mix_implicitly_explicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ImplicitlyCopyConstructible&, const ExplicitlyCopyConstructible&>));

    const auto test = []() {
        const ImplicitlyCopyConstructible obj1(1);
        const ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_copy_mix_implicitly_explicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ImplicitlyCopyConstructible&, const ExplicitlyCopyConstructible&>));

    const auto test = []() {
        const ImplicitlyCopyConstructible obj1(1);
        const ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(obj1, obj2);
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_explicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyCopyConstructible&&, ExplicitlyCopyConstructible&&>));

    const auto test = []() {
        ExplicitlyCopyConstructible obj1(1);
        ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_explicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyCopyConstructible&&, ExplicitlyCopyConstructible&&>));

    const auto test = []() {
        ExplicitlyCopyConstructible obj1(1);
        ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_implicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, ImplicitlyCopyConstructible&&, ImplicitlyCopyConstructible&&>));

    const auto test = []() {
        ImplicitlyCopyConstructible obj1(1);
        ImplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_implicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, ImplicitlyCopyConstructible&&, ImplicitlyCopyConstructible&&>));

    const auto test = []() {
        ImplicitlyCopyConstructible obj1(1);
        ImplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_mix_implicitly_explicitly_copyable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ImplicitlyCopyConstructible&&, ExplicitlyCopyConstructible&&>));

    const auto test = []() {
        ImplicitlyCopyConstructible obj1(1);
        ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_mix_implicitly_explicitly_copyable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ImplicitlyCopyConstructible&&, ExplicitlyCopyConstructible&&>));

    const auto test = []() {
        ImplicitlyCopyConstructible obj1(1);
        ExplicitlyCopyConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).copy_constructor_count() == 1u
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

TEST(Tuple, constructor_by_move_explicitly_moveable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyMoveConstructible&&, ExplicitlyMoveConstructible&&>));

    const auto test = []() {
        ExplicitlyMoveConstructible obj1(1);
        ExplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_move_explicitly_moveable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible2, ExplicitlyMoveConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyMoveConstructible&&, ExplicitlyMoveConstructible&&>));

    const auto test = []() {
        ExplicitlyMoveConstructible obj1(1);
        ExplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_move_implicitly_moveable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible, ImplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, ImplicitlyMoveConstructible&&, ImplicitlyMoveConstructible&&>));

    const auto test = []() {
        ImplicitlyMoveConstructible obj1(1);
        ImplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_move_implicitly_moveable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible2, ImplicitlyMoveConstructible2>;

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, ImplicitlyMoveConstructible&&, ImplicitlyMoveConstructible&&>));

    const auto test = []() {
        ImplicitlyMoveConstructible obj1(1);
        ImplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_move_mix_implicitly_explicitly_moveable_same_types) {
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible, ExplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ImplicitlyMoveConstructible&&, ExplicitlyMoveConstructible&&>));

    const auto test = []() {
        ImplicitlyMoveConstructible obj1(1);
        ExplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_move_mix_implicitly_explicitly_moveable_different_types) {
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible2, ExplicitlyMoveConstructible2>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ImplicitlyMoveConstructible&&, ExplicitlyMoveConstructible&&>));

    const auto test = []() {
        ImplicitlyMoveConstructible obj1(1);
        ExplicitlyMoveConstructible obj2(2);
        TupleType tuple(hud::move(obj1), hud::move(obj2));
        return std::tuple{
            hud::get<0>(tuple).id() == 1,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).id() == 2,
            hud::get<1>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).copy_constructor_count() == 0u,
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

TEST(Tuple, constructor_by_copy_pair_of_explictly_copyable_same_types) {
    using PairType = hud::Pair<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{ 1,2 };
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_copy_pair_of_explictly_copyable_different_types) {
    using PairType = hud::Pair<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{1,2};
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_copy_pair_of_implictly_copyable_same_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{ 1,2 };
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_copy_pair_of_implictly_copyable_different_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{ 1,2 };
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_copy_pair_of_mix_implictly_and_explitly_copyable_same_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{ 1,2 };
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_copy_pair_of_mix_implictly_and_explitly_copyable_different_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const PairType&>));

    const auto test = []() {
        const PairType pair{ 1,2 };
        const TupleType tuple{ pair };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_explictly_copyable_same_types) {
    using PairType = hud::Pair<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_explictly_copyable_different_types) {
    using PairType = hud::Pair<ExplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_implictly_copyable_same_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_implictly_copyable_different_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ImplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_mix_implictly_and_explitly_copyable_same_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_mix_implictly_and_explitly_copyable_different_types) {
    using PairType = hud::Pair<ImplicitlyCopyConstructible, ExplicitlyCopyConstructible>;
    using TupleType = hud::Tuple<ImplicitlyCopyConstructible2, ExplicitlyCopyConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_explictly_moveable_same_types) {
    using PairType = hud::Pair<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>;


   // ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));
    static_assert((hud::IsExplicitlyMoveConstructibleV<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>));
    static_assert((hud::details::IsPairExplictlyMoveConstructibleToTupleV < PairType, TupleType>));
    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_explictly_moveable_different_types) {
    using PairType = hud::Pair<ExplicitlyMoveConstructible, ExplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible2, ExplicitlyMoveConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_implictly_moveable_same_types) {
    using PairType = hud::Pair<ImplicitlyMoveConstructible, ImplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible, ImplicitlyMoveConstructible>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_implictly_moveable_different_types) {
    using PairType = hud::Pair<ImplicitlyMoveConstructible, ImplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible2, ImplicitlyMoveConstructible2>;


    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_mix_implictly_and_explitly_moveable_same_types) {
    using PairType = hud::Pair<ImplicitlyMoveConstructible, ExplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible, ExplicitlyMoveConstructible>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, constructor_by_move_pair_of_mix_implictly_and_explitly_moveable_different_types) {
    using PairType = hud::Pair<ImplicitlyMoveConstructible, ExplicitlyMoveConstructible>;
    using TupleType = hud::Tuple<ImplicitlyMoveConstructible2, ExplicitlyMoveConstructible2>;


    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, PairType&&>));

    const auto test = []() {
        PairType pair{ 1,2 };
        const TupleType tuple{ hud::move(pair) };
        return std::tuple{
            hud::get<0>(tuple).id(),
            hud::get<0>(tuple).copy_constructor_count() == 0u,
            hud::get<0>(tuple).move_constructor_count() == 1u,
            hud::get<1>(tuple).id(),
            hud::get<1>(tuple).copy_constructor_count() == 0u,
            hud::get<1>(tuple).move_constructor_count() == 1u,
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

TEST(Tuple, copy_constructor_copyable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyCopyConstructible&, const ImplicitlyCopyConstructible&>));

    const auto test = []() {
        const TupleType to_copy{ 1,2 };
        const TupleType copy{ to_copy };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
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

TEST(Tuple, copy_constructor_copyable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;
    using OtherTupleType = hud::Tuple<ExplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyCopyConstructible&, const ImplicitlyCopyConstructible&>));

    const auto test = []() {
        const OtherTupleType to_copy{ 1,2 };
        const TupleType copy{ to_copy };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
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

TEST(Tuple, copy_constructor_moveable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible, ImplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyMoveConstructible&, const ExplicitlyMoveConstructible&>));

    const auto test = []() {
        const TupleType to_copy{ 1,2 };
        const TupleType copy{ to_copy };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<0>(copy).move_constructor_count() == 0u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).move_constructor_count() == 0u,
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

TEST(Tuple, copy_constructor_moveable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible2, ImplicitlyMoveConstructible2>;
    using OtherTupleType = hud::Tuple<ExplicitlyMoveConstructible, ImplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, const ExplicitlyMoveConstructible&, const ImplicitlyMoveConstructible&>));

    const auto test = []() {
        const OtherTupleType to_copy{ 1,2 };
        const TupleType copy{ to_copy };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<0>(copy).move_constructor_count() == 0u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).move_constructor_count() == 0u,
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

TEST(Tuple, move_constructor_copyable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyCopyConstructible&&, ImplicitlyCopyConstructible&&>));

    const auto test = []() {
        TupleType to_copy{ 1,2 };
        const TupleType copy{ hud::move(to_copy) };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
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

TEST(Tuple, move_constructor_copyable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyCopyConstructible2, ImplicitlyCopyConstructible2>;
    using OtherTupleType = hud::Tuple<ExplicitlyCopyConstructible, ImplicitlyCopyConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyCopyConstructible&&, ImplicitlyCopyConstructible&&>));

    const auto test = []() {
        OtherTupleType to_copy{ 1,2 };
        const TupleType copy{ hud::move(to_copy) };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 1u,
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

TEST(Tuple, move_constructor_moveable_same_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible, ImplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyMoveConstructible&&, ImplicitlyMoveConstructible&&>));

    const auto test = []() {
        TupleType to_copy{ 1,2 };
        const TupleType copy{ hud::move(to_copy) };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 0u,
            hud::get<0>(copy).move_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 0u,
            hud::get<1>(copy).move_constructor_count() == 1u,
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

TEST(Tuple, move_constructor_moveable_different_types) {
    using TupleType = hud::Tuple<ExplicitlyMoveConstructible2, ImplicitlyMoveConstructible2>;
    using OtherTupleType = hud::Tuple<ExplicitlyMoveConstructible, ImplicitlyMoveConstructible>;

    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<TupleType, ExplicitlyMoveConstructible&&, ImplicitlyMoveConstructible&&>));

    const auto test = []() {
        OtherTupleType to_copy{ 1,2 };
        const TupleType copy{ hud::move(to_copy) };
        return std::tuple{
            hud::get<0>(copy).id() == 1,
            hud::get<0>(copy).copy_constructor_count() == 0u,
            hud::get<0>(copy).move_constructor_count() == 1u,
            hud::get<1>(copy).id() == 2,
            hud::get<1>(copy).copy_constructor_count() == 0u,
            hud::get<1>(copy).move_constructor_count() == 1u,
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
