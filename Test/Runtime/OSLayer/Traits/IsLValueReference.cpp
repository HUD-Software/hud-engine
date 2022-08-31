#include <OSLayer/Traits/IsLValueReference.h>


TEST(Traits, IsLValueReference) {
    ASSERT_FALSE(hud::IsLValueReferenceV<i32>);
    ASSERT_TRUE(hud::IsLValueReferenceV<i32&>);
    ASSERT_FALSE(hud::IsLValueReferenceV<i32&&>);
}