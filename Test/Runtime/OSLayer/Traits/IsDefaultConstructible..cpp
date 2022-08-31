#include <OSLayer/Traits/IsDefaultConstructible.h>

namespace {
    struct A { };
    struct B { B() {} };
    struct C { C(int) {} };
}

TEST(Traits, IsDefaultConstructible) {
    ASSERT_TRUE((hud::IsDefaultConstructibleV<i32>));
    ASSERT_FALSE((hud::IsDefaultConstructibleV<i32&>));
    ASSERT_TRUE((hud::IsDefaultConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsDefaultConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsDefaultConstructibleV<const volatile i32>));
    ASSERT_TRUE((hud::IsDefaultConstructibleV<A>));
    ASSERT_TRUE((hud::IsDefaultConstructibleV<B>));
    ASSERT_FALSE((hud::IsDefaultConstructibleV<C>));
}