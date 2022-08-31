#include <OSLayer/Traits/IsRValueReference.h>

TEST(Traits, IsRValueReference) {
    ASSERT_FALSE((hud::IsRValueReferenceV<i32>));
    ASSERT_FALSE((hud::IsRValueReferenceV<i32&>));
    ASSERT_TRUE((hud::IsRValueReferenceV<i32&&>));
}