#include <OSLayer/Traits/IsMoveConstructible.h>

namespace {
    struct A { };
    struct B { B(B&&) = delete; };
    struct C { C(B&&) noexcept { } };
}

TEST(Traits, IsMoveConstructible) {
    ASSERT_TRUE((hud::IsMoveConstructibleV<i32>));
    ASSERT_TRUE((hud::IsMoveConstructibleV<A>));
    ASSERT_FALSE((hud::IsMoveConstructibleV<B>));
    ASSERT_TRUE((hud::IsMoveConstructibleV<C, B>));
    ASSERT_FALSE((hud::IsMoveConstructibleV<B, C>));
}