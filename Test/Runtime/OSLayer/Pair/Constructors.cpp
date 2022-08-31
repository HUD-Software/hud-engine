#include <OSLayer/Containers/Pair.h>
#include <OSLayer/Traits/IsExplicitlyDefaultConstructible.h>
#include <OSLayer/Traits/IsImplicitlyDefaultConstructible.h>
#include <OSLayer/Traits/IsExplicitlyCopyConstructible.h>
#include <OSLayer/Traits/IsImplicitlyCopyConstructible.h>
#include <OSLayer/Traits/IsExplicitlyMoveConstructible.h>
#include <OSLayer/Traits/IsImplicitlyMoveConstructible.h>
#include <OSLayer/Traits/IsExplicitlyConstructible.h>
#include <OSLayer/Traits/IsImplicitlyConstructible.h>
#include <OSLayer/Traits/IsTriviallyDefaultConstructible.h>

struct Implicit {
    Implicit() noexcept = default;
    Implicit(wchar value) noexcept
        : mInner(value) {
    }
    Implicit(const Implicit& other) noexcept
        : mInner(other.mInner) {
    };
    Implicit(Implicit&& other) noexcept
        : mInner(other.mInner + 1) {
    };
    wchar mInner = L'\0';
};
static_assert(hud::IsImplicitlyDefaultConstructibleV<Implicit>);
static_assert(!hud::IsExplicitlyDefaultConstructibleV<Implicit>);
static_assert(hud::IsImplicitlyConstructibleV<Implicit, wchar>);
static_assert(!hud::IsExplicitlyConstructibleV<Implicit, wchar>);
static_assert(hud::IsImplicitlyConstructibleV<Implicit, const Implicit&>);
static_assert(!hud::IsExplicitlyConstructibleV<Implicit, const Implicit&>);
static_assert(hud::IsImplicitlyConstructibleV<Implicit, Implicit&&>);
static_assert(!hud::IsExplicitlyConstructibleV<Implicit, Implicit&&>);
static_assert(hud::IsConvertibleV<const Implicit&, Implicit>);

struct Explicit {
    explicit Explicit() noexcept = default;
    explicit Explicit(i32 value) noexcept
        : mInner(value) {
    }
    explicit Explicit(const Explicit& other) noexcept
        : mInner(other.mInner) {
    };

    explicit Explicit(Explicit&& other) noexcept
        : mInner(other.mInner + 1) {
    }; 
    operator Implicit() const noexcept { return Implicit(static_cast<wchar>(mInner)); }
    i32 mInner = 0;
};
static_assert(!hud::IsImplicitlyDefaultConstructibleV<Explicit>);
static_assert(hud::IsExplicitlyDefaultConstructibleV<Explicit>);
static_assert(!hud::IsImplicitlyConstructibleV<Explicit, i32>);
static_assert(hud::IsExplicitlyConstructibleV<Explicit, i32>);

static_assert(!hud::IsImplicitlyConstructibleV<Explicit, const Explicit&>);
static_assert(hud::IsExplicitlyConstructibleV<Explicit, const Explicit&>);
static_assert(!hud::IsImplicitlyConstructibleV<Explicit, Explicit&&>);
static_assert(hud::IsExplicitlyConstructibleV<Explicit, Explicit&&>);
static_assert(!hud::IsConvertibleV<const Explicit&, Explicit>);

TEST(Pair, default_constructor_is_explicit_if_T1_or_T2_is_not_implicitly_default_constructible) {
    using namespace hud;

    static_assert(IsImplicitlyDefaultConstructibleV<Implicit>);
    static_assert(IsImplicitlyDefaultConstructibleV<Pair<i32, i32>>);
    static_assert(IsImplicitlyDefaultConstructibleV<Pair<i32, f32>>);
    static_assert(IsImplicitlyDefaultConstructibleV<Pair<i32,Implicit>>);
    static_assert(IsImplicitlyDefaultConstructibleV<Pair<Implicit, Implicit>>);
    static_assert(IsExplicitlyDefaultConstructibleV<Pair<i32, Explicit>>);
    static_assert(IsExplicitlyDefaultConstructibleV<Pair<i32, Explicit>>);
    static_assert(IsExplicitlyDefaultConstructibleV<Pair<Explicit, Explicit>>);
}


TEST(Pair, param_copy_constructor_is_explicit_if_T1_or_T2_is_not_implicitly_convertible) {
    using namespace hud;

    static_assert(IsConvertibleV<const Explicit&, Implicit>);
    static_assert(IsConvertibleV<const Implicit&, Implicit>);
    static_assert(IsImplicitlyConstructibleV<Pair<Implicit, Implicit>, const Implicit&, const Implicit&>);
    static_assert(IsImplicitlyConstructibleV<Pair<Implicit, Implicit>, const Implicit&, wchar>);
    static_assert(IsExplicitlyConstructibleV<Pair<Explicit, Implicit>, const Explicit&, const Implicit&>);
    static_assert(IsExplicitlyConstructibleV<Pair<Explicit, Implicit>, i32, const Implicit&>);
}

TEST(Pair, param_move_constructor_is_explicit_if_T1_or_T2_is_not_implicitly_converible) {
    using namespace hud;

    static_assert(IsConvertibleV<const Explicit&, Implicit>);
    static_assert(IsConvertibleV<const Implicit&, Implicit>);
    static_assert(IsImplicitlyConstructibleV<Pair<Implicit, Implicit>, Implicit&&, Implicit&&>);
    static_assert(IsImplicitlyConstructibleV<Pair<Implicit, Implicit>, Implicit&&, wchar>);
    static_assert(IsExplicitlyConstructibleV<Pair<Explicit, Implicit>, Explicit&&, Implicit&&>);
    static_assert(IsExplicitlyConstructibleV<Pair<Explicit, Implicit>, i32, Implicit&&>);
}

TEST(Pair, copy_constructor_is_explicit_if_T1_or_T2_is_not_implicitly_convertible) {
    using namespace hud;

    static_assert(IsConvertibleV<const Explicit&, Implicit>);
    static_assert(IsConvertibleV<const Implicit&, Implicit>);
    static_assert(IsCopyConstructibleV<Explicit, Explicit>);
    static_assert(IsCopyConstructibleV<Implicit, Implicit>);

    // Same
    static_assert(IsImplicitlyCopyConstructibleV < Pair<Implicit, Implicit>, Pair<Implicit, Implicit>>);
    static_assert(IsExplicitlyCopyConstructibleV < Pair<Explicit, Implicit>, Pair<Explicit, Implicit>> );
    
    // Not same T
    static_assert(IsImplicitlyCopyConstructibleV < Pair<Implicit, Implicit>, Pair<Implicit, wchar>>);
    static_assert(IsExplicitlyCopyConstructibleV < Pair<Explicit, Implicit>, Pair <i32, Implicit>>);
    static_assert(IsImplicitlyCopyConstructibleV < Pair<Implicit, Implicit>, Pair<i32, wchar>>);
}

TEST(Pair, move_constructor_is_explicit_if_T1_or_T2_is_not_implicitly_convertible) {
    using namespace hud;

    static_assert(IsConvertibleV<Explicit, Implicit>);
    static_assert(IsConvertibleV<Implicit, Implicit>);
    static_assert(IsMoveConstructibleV<Explicit, Explicit>);
    static_assert(IsMoveConstructibleV<Implicit, Implicit>);

    // Same
    static_assert(IsImplicitlyMoveConstructibleV < Pair<Implicit, Implicit>, Pair<Implicit, Implicit>>);
    static_assert(IsExplicitlyMoveConstructibleV < Pair<Explicit, Implicit>, Pair<Explicit, Implicit>>);
    static_assert(IsExplicitlyMoveConstructibleV < Pair<Explicit, Implicit>, Pair <i32, Implicit>>);

    // Not same T
    static_assert(IsImplicitlyMoveConstructibleV < Pair<Implicit, Implicit>, Pair<Implicit, wchar>>);
    static_assert(IsExplicitlyMoveConstructibleV < Pair<Explicit, Implicit>, Pair <i32, Implicit>>);
    static_assert(IsExplicitlyMoveConstructibleV < Pair<Explicit, Implicit>, Pair <i32, wchar>>);
}


TEST(Pair, default_constructor_trivial) {
    using namespace hud;
    using Type1 = i32;
    using Type2 = f32;
    static_assert(IsTriviallyDefaultConstructibleV<Type1>);
    static_assert(IsTriviallyDefaultConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = []() {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair);
        const auto result = std::tuple{ pair->first, pair->second };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_EQ(std::get<0>(result), 0);
        ASSERT_EQ(std::get<1>(result), 0.0f);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_EQ(std::get<0>(result), 0);
        ASSERT_EQ(std::get<1>(result), 0.0f);
    }
}

TEST(Pair, default_constructor_non_trivial) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseType;
    using Type2 = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyDefaultConstructibleV<Type1>);
    static_assert(!IsTriviallyDefaultConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = []() {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair);
        const auto result = std::tuple{ 
            pair->first.move_assign_count(),
            pair->first.copy_assign_count(),
            pair->first.constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.move_assign_count(),
            pair->second.copy_assign_count(),
            pair->second.constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 0);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 0u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 0);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 0u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 0);
    }
}

TEST(Pair, copy_constructor_trivial_type_same_type) {
    using namespace hud;
    using Type1 = i32;
    using Type2 = f32;
    static_assert(IsTriviallyCopyConstructibleV<Type1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const Type1& t1, const Type2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const TypePair other{ t1, t2 };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123,456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }

    // Constant
    {
        constexpr auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }
}

TEST(Pair, copy_constructor_non_trivial_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseType;
    using Type2 = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const TypePair other{ {id1, nullptr}, {id2, nullptr } };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first.move_assign_count(),
            pair->first.copy_assign_count(),
            pair->first.constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.move_assign_count(),
            pair->second.copy_assign_count(),
            pair->second.constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123,456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123,456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 456);
    }
}

TEST(Pair, copy_constructor_non_trivial_copy_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const TypePair other{ id1,  id2 };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, copy_constructor_trivial_type_different_type) {
    using namespace hud;
    using Type1 = i64;
    using Type2 = i32;
    using OtherType1 = i16;
    using OtherType2 = i8;
    static_assert(IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const OtherType1& t1, const OtherType2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const OtherTypePair other{ t1, t2 };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }

    // Constant
    {
        constexpr auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }
}

TEST(Pair, copy_constructor_non_trivial_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const OtherTypePair other{ id1, id2 };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}
           
TEST(Pair, copy_constructor_non_trivial_copy_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const OtherTypePair other{ id1, id2 };
        Memory::construct_at(pair, other);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, move_constructor_trivial_type_same_type) {
    using namespace hud;
    using Type1 = i32;
    using Type2 = f32;
    static_assert(IsTriviallyCopyConstructibleV<Type1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const Type1& t1, const Type2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        TypePair other{ t1, t2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }

    // Constant
    {
        constexpr auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }
}

TEST(Pair, move_constructor_non_trivial_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseType;
    using Type2 = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        TypePair other{ {id1, nullptr}, {id2, nullptr } };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first.move_assign_count(),
            pair->first.copy_assign_count(),
            pair->first.constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.move_assign_count(),
            pair->second.copy_assign_count(),
            pair->second.constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 2u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 2u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 2u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 456);
    }
}

TEST(Pair, move_constructor_non_trivial_copy_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        TypePair other{ id1,  id2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, move_constructor_non_trivial_move_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseMoveConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseMoveConstructibleType;
    static_assert(!IsTriviallyMoveConstructibleV<Type1>);
    static_assert(!IsTriviallyMoveConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        TypePair other{ id1,  id2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }
}

TEST(Pair, move_constructor_trivial_type_different_type) {
    using namespace hud;
    using Type1 = i64;
    using Type2 = i32;
    using OtherType1 = i16;
    using OtherType2 = i8;
    static_assert(IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const OtherType1& t1, const OtherType2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherTypePair other{ t1, t2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }

    // Constant
    {
        constexpr auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }
}

TEST(Pair, move_constructor_non_trivial_copy_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherTypePair other{ id1, id2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, move_constructor_non_trivial_move_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseMoveConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseMoveConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseMoveConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseMoveConstructibleType;
    static_assert(IsMoveConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyMoveConstructibleV<Type1, OtherType1>);
    static_assert(IsMoveConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyMoveConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;
    using OtherTypePair = Pair<OtherType1, OtherType2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherTypePair other{ id1, id2 };
        Memory::construct_at(pair, move(other));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }
}

TEST(Pair, param_copy_constructor_trivial_type_same_type) {
    using namespace hud;
    using Type1 = i32;
    using Type2 = f32;
    static_assert(IsTriviallyCopyConstructibleV<Type1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const Type1& t1, const Type2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }

    // Constant
    {
        constexpr auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }
}

TEST(Pair, param_copy_constructor_trivial_type_different_type) {
    using namespace hud;
    using Type1 = i64;
    using Type2 = i32;
    using OtherType1 = i16;
    using OtherType2 = i8;
    static_assert(IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const OtherType1& t1, const OtherType2& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }

    // Constant
    {
        constexpr auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }
}

TEST(Pair, param_copy_constructor_non_trivial_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseType;
    using Type2 = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const Type1 t1{ id1, nullptr };
        const Type2 t2{ id2, nullptr };
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first.move_assign_count(),
            pair->first.copy_assign_count(),
            pair->first.constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.move_assign_count(),
            pair->second.copy_assign_count(),
            pair->second.constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 0u);
        ASSERT_EQ(std::get<10>(result), 1u);
        ASSERT_EQ(std::get<11>(result), 456);
    }
}

TEST(Pair, param_copy_constructor_non_trivial_copy_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const Type1 t1{ id1 };
        const Type2 t2{ id2 };
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_copy_constructor_non_trivial_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const OtherType1 t1{ id1 };
        const OtherType2 t2{ id2 };
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_copy_constructor_non_trivial_copy_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        const OtherType1 t1{ id1 };
        const OtherType2 t2{ id2 };
        Memory::construct_at(pair, t1, t2);
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_move_constructor_trivial_type_same_type) {
    using namespace hud;
    using Type1 = i32;
    using Type2 = f32;
    static_assert(IsTriviallyCopyConstructibleV<Type1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](Type1&& t1, Type2&& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair, forward<Type1>(t1), forward<Type2>(t2));
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }

    // Constant
    {
        constexpr auto result = test(123, 456.0f);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 456.0f);
    }
}

TEST(Pair, param_move_constructor_non_trivial_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseType;
    using Type2 = HUD_TEST::NonBitwiseType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Type1 t1{ id1, nullptr };
        Type2 t2{ id2, nullptr };
        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.move_assign_count(),
            pair->first.copy_assign_count(),
            pair->first.constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.move_assign_count(),
            pair->second.copy_assign_count(),
            pair->second.constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 0u);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 1u);
        ASSERT_EQ(std::get<4>(result), 0u);
        ASSERT_EQ(std::get<5>(result), 123);

        ASSERT_EQ(std::get<6>(result), 0u);
        ASSERT_EQ(std::get<7>(result), 0u);
        ASSERT_EQ(std::get<8>(result), 1u);
        ASSERT_EQ(std::get<9>(result), 1u);
        ASSERT_EQ(std::get<10>(result), 0u);
        ASSERT_EQ(std::get<11>(result), 456);
    }
}

TEST(Pair, param_move_constructor_non_trivial_copy_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(!IsTriviallyCopyConstructibleV<Type1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Type1 t1{ id1 };
        Type2 t2{ id2 };
        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_move_constructor_non_trivial_move_constructible_type_same_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseMoveConstructibleType;
    using Type2 = HUD_TEST::NonBitwiseMoveConstructibleType;
    static_assert(!IsTriviallyMoveConstructibleV<Type1>);
    static_assert(!IsTriviallyMoveConstructibleV<Type2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Type1 t1{ id1 };
        Type2 t2{ id2 };

        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }
}

TEST(Pair, param_move_constructor_trivial_type_different_type) {
    using namespace hud;
    using Type1 = i64;
    using Type2 = i32;
    using OtherType1 = i16;
    using OtherType2 = i8;
    static_assert(IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](OtherType1&& t1, OtherType2&& t2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        Memory::construct_at(pair, forward<OtherType1>(t1), forward<OtherType2>(t2));
        const auto result = std::tuple{
            pair->first,
            pair->second
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }

    // Constant
    {
        constexpr auto result = test(123, 32);
        ASSERT_EQ(std::get<0>(result), 123);
        ASSERT_EQ(std::get<1>(result), 32);
    }
}

TEST(Pair, param_move_constructor_non_trivial_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherType1 t1{ id1 };
        OtherType2 t2{ id2 };
        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_move_constructor_non_trivial_copy_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseCopyConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseCopyConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseCopyConstructibleType;
    static_assert(IsCopyConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyCopyConstructibleV<Type1, OtherType1>);
    static_assert(IsCopyConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyCopyConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherType1 t1{ id1 };
        OtherType2 t2{ id2 };
        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 1u);
        ASSERT_EQ(std::get<1>(result), 123);
        ASSERT_EQ(std::get<2>(result), 1u);
        ASSERT_EQ(std::get<3>(result), 456);
    }
}

TEST(Pair, param_move_constructor_non_trivial_move_constructible_type_different_type) {
    using namespace hud;
    using Type1 = HUD_TEST::NonBitwiseMoveConstructibleType2;
    using Type2 = HUD_TEST::NonBitwiseMoveConstructibleType2;
    using OtherType1 = HUD_TEST::NonBitwiseMoveConstructibleType;
    using OtherType2 = HUD_TEST::NonBitwiseMoveConstructibleType;
    static_assert(IsMoveConstructibleV<Type1, OtherType1>);
    static_assert(!IsTriviallyMoveConstructibleV<Type1, OtherType1>);
    static_assert(IsMoveConstructibleV<Type2, OtherType2>);
    static_assert(!IsTriviallyMoveConstructibleV<Type2, OtherType2>);
    using TypePair = Pair<Type1, Type2>;

    const auto test = [](const i32& id1, const i32& id2) {
        TypePair* pair = Memory::allocate_array<TypePair>(1);
        OtherType1 t1{ id1 };
        OtherType2 t2{ id2 };

        Memory::construct_at(pair, move(t1), move(t2));
        const auto result = std::tuple{
            pair->first.copy_constructor_count(),
            pair->first.move_constructor_count(),
            pair->first.id(),
            pair->second.copy_constructor_count(),
            pair->second.move_constructor_count(),
            pair->second.id(),
        };
        Memory::free_array(pair, 1);
        return result;
    };

    // Non constant
    {
        const auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }

    // Constant
    {
        constexpr auto result = test(123, 456);
        ASSERT_EQ(std::get<0>(result), 0u);
        ASSERT_EQ(std::get<1>(result), 1u);
        ASSERT_EQ(std::get<2>(result), 123);
        ASSERT_EQ(std::get<3>(result), 0u);
        ASSERT_EQ(std::get<4>(result), 1u);
        ASSERT_EQ(std::get<5>(result), 456);
    }
};