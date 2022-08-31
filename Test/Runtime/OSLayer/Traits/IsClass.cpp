#include <OSLayer/Traits/IsClass.h>

TEST(Traits, IsClass) {
    ASSERT_FALSE(hud::IsClassV<i32>);
    ASSERT_FALSE(hud::IsClassV<i32*>);
    ASSERT_FALSE(hud::IsClassV<i32&>);
    ASSERT_TRUE(hud::IsClassV<class A>);
    ASSERT_TRUE(hud::IsClassV<struct S>);
}