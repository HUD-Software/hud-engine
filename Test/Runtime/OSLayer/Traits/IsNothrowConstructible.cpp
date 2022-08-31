#include <OSLayer/Traits/IsNothrowConstructible.h>

namespace {
    struct A { };
    struct B {
        B() {}
        B(const A&) noexcept {}
        B(A&&) noexcept {}
    };
}

TEST(Traits, IsNothrowConstructible) {
    ASSERT_TRUE((hud::IsNothrowConstructibleV<i32>));
    ASSERT_TRUE((hud::IsNothrowConstructibleV<A>));
    ASSERT_FALSE((hud::IsNothrowConstructibleV<B>));
    ASSERT_TRUE((hud::IsNothrowConstructibleV<B, A&>));
    ASSERT_TRUE((hud::IsNothrowConstructibleV<B, A&&>));
}