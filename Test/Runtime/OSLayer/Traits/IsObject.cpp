#include <OSLayer/Traits/IsObject.h>

namespace {
    class A {};
}

TEST(Traits, IsObject) {
    ASSERT_TRUE((hud::IsObjectV<i32>));
    ASSERT_TRUE((hud::IsObjectV<A>));
    ASSERT_FALSE((hud::IsObjectV<A&>));
    ASSERT_TRUE((hud::IsObjectV<A*>));
    ASSERT_FALSE((hud::IsObjectV<i32(i32)>));
    ASSERT_TRUE((hud::IsObjectV<i32(*)(i32)>));
}