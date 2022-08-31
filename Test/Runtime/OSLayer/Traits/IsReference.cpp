#include <OSLayer/Traits/IsReference.h>

TEST(traits, IsReference) {
    ASSERT_FALSE((hud::IsReferenceV<i32>));
    ASSERT_FALSE((hud::IsReferenceV<i32*>));
    ASSERT_TRUE((hud::IsReferenceV<i32&>));
    ASSERT_TRUE((hud::IsReferenceV<i32&&>));
}