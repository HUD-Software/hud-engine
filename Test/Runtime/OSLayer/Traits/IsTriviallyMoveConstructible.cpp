#include <OSLayer/Traits/IsTriviallyMoveConstructible.h>

namespace {
    struct A { };
    struct B { B(B&&) noexcept {} };
    struct C { virtual void fn() {} };
}

TEST(Traits, IsTriviallyMoveConstructible) {
    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<i32>));
    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyMoveConstructibleV<i32[]>));
    ASSERT_FALSE((hud::IsTriviallyMoveConstructibleV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<i32*>));
    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<i32, f32>));

    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<A>));
    ASSERT_TRUE((hud::IsTriviallyMoveConstructibleV<A, A>));
    ASSERT_FALSE((hud::IsTriviallyMoveConstructibleV<B>));
    ASSERT_FALSE((hud::IsTriviallyMoveConstructibleV<C>));
    ASSERT_FALSE((hud::IsTriviallyMoveConstructibleV<C, C>));
}