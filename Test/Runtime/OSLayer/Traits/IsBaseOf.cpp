#include <OSLayer/Traits/IsBaseOf.h>

namespace {
    class A {};
    class B : A {};
    class C {};
}

TEST(Traits, IsBaseOf) {

    ASSERT_TRUE((hud::IsBaseOfV<A, A>));
    ASSERT_TRUE((hud::IsBaseOfV<A, B>));
    ASSERT_FALSE((hud::IsBaseOfV<A, C>));
    ASSERT_FALSE((hud::IsBaseOfV<B, A>));
    ASSERT_TRUE((hud::IsBaseOfV<B, B>));
    ASSERT_FALSE((hud::IsBaseOfV<B, C>));
    ASSERT_FALSE((hud::IsBaseOfV<C, A>));
    ASSERT_FALSE((hud::IsBaseOfV<C, B>));
    ASSERT_TRUE((hud::IsBaseOfV<C, C>));

    ASSERT_FALSE((hud::IsBaseOfV<A*, A*>));
    ASSERT_FALSE((hud::IsBaseOfV<A*, B*>));
    ASSERT_FALSE((hud::IsBaseOfV<A*, C*>));
}
