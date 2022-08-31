#include <OSLayer/Traits/IsTriviallyDestructible.h>

namespace {
    struct A { };
    struct B { ~B() {} };
}

TEST(Traits, IsTriviallyDestructible) {
    ASSERT_TRUE((hud::IsTriviallyDestructibleV<i32>));
    ASSERT_TRUE((hud::IsTriviallyDestructibleV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyDestructibleV<i32[]>));
    ASSERT_TRUE((hud::IsTriviallyDestructibleV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyDestructibleV<i32*>));

    ASSERT_TRUE((hud::IsTriviallyDestructibleV<A>));
    ASSERT_FALSE((hud::IsTriviallyDestructibleV<B>));
}