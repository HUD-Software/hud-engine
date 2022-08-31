#include <OSLayer/Traits/IsTriviallyDefaultConstructible.h>

namespace {
    struct A { };
    struct B { B() {} };
    struct C { virtual void fn() {} };
}

TEST(Traits, IsTriviallyDefaultConstructible) {
    ASSERT_TRUE((hud::IsTriviallyDefaultConstructibleV<i32>));
    ASSERT_FALSE((hud::IsTriviallyDefaultConstructibleV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyDefaultConstructibleV<i32[]>));
    ASSERT_TRUE((hud::IsTriviallyDefaultConstructibleV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyDefaultConstructibleV<i32*>));

    ASSERT_TRUE((hud::IsTriviallyDefaultConstructibleV<A>));
    ASSERT_FALSE((hud::IsTriviallyDefaultConstructibleV<B>));
    ASSERT_FALSE((hud::IsTriviallyDefaultConstructibleV<C>));
}