#include <OSLayer/Traits/IsArray.h>

namespace {
    class A {};
}

TEST(Traits, IsArray) {
    ASSERT_FALSE(hud::IsArrayV<A>);
    ASSERT_FALSE(hud::IsArrayV<A*>);
    ASSERT_TRUE(hud::IsArrayV<A[]>);
    ASSERT_TRUE(hud::IsArrayV<A[][2]>);
    ASSERT_TRUE(hud::IsArrayV<A[2]>);
    ASSERT_TRUE(hud::IsArrayV<A[2][2]>);
}