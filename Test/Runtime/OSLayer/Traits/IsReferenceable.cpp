#include <OSLayer/Traits/IsReferenceable.h>

TEST(Traits, IsReferenceable) {
    ASSERT_TRUE((hud::IsReferenceableV<i32>));
    ASSERT_TRUE((hud::IsReferenceableV<i32&>));
    ASSERT_TRUE((hud::IsReferenceableV<i32&&>));
    ASSERT_TRUE((hud::IsReferenceableV<i32*>));
    ASSERT_TRUE((hud::IsReferenceableV<i32(*)(i32)>));
    ASSERT_FALSE((hud::IsReferenceableV<int()const >));
}