#include <OSLayer/Traits/IsPointer.h>

TEST(Traits, IsPointer) {
    ASSERT_FALSE((hud::IsPointerV<i32>));
    ASSERT_TRUE((hud::IsPointerV<i32*>));
    ASSERT_TRUE((hud::IsPointerV<i32**>));
    ASSERT_TRUE((hud::IsPointerV<i32(*)(i32)>));
}