#include <OSLayer/Traits/IsNothrowDestructible.h>

namespace {
    struct A { };
    struct B { ~B() {} };
    struct C { ~C() noexcept(false) {} };
}

TEST(Traits, IsNothrowDestructible) {
    ASSERT_TRUE((hud::IsNothrowDestructibleV<i32>));
    ASSERT_TRUE((hud::IsNothrowDestructibleV<A>));
    ASSERT_TRUE((hud::IsNothrowDestructibleV<B>));
    ASSERT_FALSE((hud::IsNothrowDestructibleV<C>));
}