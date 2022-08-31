#include <OSLayer/Traits/IsUnion.h>

namespace {
    class A {};
    union B {};
    struct C {
        union D {};
    };
}

TEST(Traits, IsUnion) {
    ASSERT_FALSE((hud::IsUnionV<i32>));
    ASSERT_FALSE((hud::IsUnionV<i32&>));
    ASSERT_FALSE((hud::IsUnionV<i32[]>));
    ASSERT_FALSE((hud::IsUnionV<i32[32]>));
    ASSERT_FALSE((hud::IsUnionV<i32*>));

    ASSERT_FALSE((hud::IsUnionV<A>));
    ASSERT_TRUE((hud::IsUnionV<B>));
    ASSERT_FALSE((hud::IsUnionV<C>));
    ASSERT_TRUE((hud::IsUnionV<C::D>));
}