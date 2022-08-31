#include <OSLayer/Traits/IsNothrowCopyConstructible.h>

namespace {
    struct A { };
    struct B {
        B(const B&) {}
    };
    struct C {
        C(const C&) noexcept {}
        C(const B&) noexcept {}
        C(const A&) {}
    };
}

TEST(Traits, IsNothrowCopyConstructible) {
    ASSERT_TRUE((hud::IsNothrowCopyConstructibleV<i32>));
    ASSERT_TRUE((hud::IsNothrowCopyConstructibleV<A>));
    ASSERT_FALSE((hud::IsNothrowCopyConstructibleV<B>));
    ASSERT_TRUE((hud::IsNothrowCopyConstructibleV<C>));
    ASSERT_TRUE((hud::IsNothrowCopyConstructibleV<C, B>));
    ASSERT_FALSE((hud::IsNothrowCopyConstructibleV<C, A>));
}
