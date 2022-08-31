#include <OSLayer/Traits/IsUnboundedArray.h>

TEST(Traits, IsUnboundedArray) {
    ASSERT_FALSE((hud::IsUnboundedArrayV<i32>));
    ASSERT_FALSE((hud::IsUnboundedArrayV<i32&>));
    ASSERT_TRUE((hud::IsUnboundedArrayV<i32[]>));
    ASSERT_FALSE((hud::IsUnboundedArrayV<i32[32]>));
    ASSERT_FALSE((hud::IsUnboundedArrayV<i32*>));
}
