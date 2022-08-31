#include <OSLayer/Traits/IsBoundedArray.h>


TEST(Traits, IsBoundedArray) {
    ASSERT_FALSE(hud::IsBoundedArrayV<i32>);
    ASSERT_FALSE(hud::IsBoundedArrayV<i32*>);
    ASSERT_FALSE(hud::IsBoundedArrayV<i32&>);
    ASSERT_FALSE(hud::IsBoundedArrayV<i32[][2]>);
    ASSERT_TRUE(hud::IsBoundedArrayV<i32[2]>);
    ASSERT_TRUE(hud::IsBoundedArrayV<i32[2][2]>);
}