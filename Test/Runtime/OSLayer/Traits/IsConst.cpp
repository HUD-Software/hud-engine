#include <OSLayer/Traits/IsConst.h>

TEST(Traits, IsConst) {
    ASSERT_FALSE(hud::IsConstV<int>);
    ASSERT_FALSE(hud::IsConstV<volatile int>);
    ASSERT_TRUE(hud::IsConstV<const int>);
    ASSERT_TRUE(hud::IsConstV<const volatile int>);
    ASSERT_FALSE(hud::IsConstV<const int*>);
    ASSERT_TRUE(hud::IsConstV<const int* const>);
    ASSERT_FALSE(hud::IsConstV<const int&>);
    ASSERT_FALSE(hud::IsConstV<int&>);
}