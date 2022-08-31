#include <OSLayer/Traits/IsNothrowMoveConstructible.h>

namespace {
    struct A { };
    struct B {
        B(B&&) {}
    };
    struct C {
        C(C&&) noexcept {}
        C(A&&) noexcept {}
        C(B&&) {}
    };
}

TEST(Traits, IsNothrowMoveConstructible) {
    ASSERT_TRUE((hud::IsNothrowMoveConstructibleV<i32>));
    ASSERT_TRUE((hud::IsNothrowMoveConstructibleV<A>));
    ASSERT_FALSE((hud::IsNothrowMoveConstructibleV<B>));
    ASSERT_TRUE((hud::IsNothrowMoveConstructibleV<C>));
    ASSERT_TRUE((hud::IsNothrowMoveConstructibleV<C, A>));
    ASSERT_FALSE((hud::IsNothrowMoveConstructibleV<C, B>));
}