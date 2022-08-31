#include <OSLayer/Traits/RemoveAllExtents.h>


TEST(Traits, RemoveAllExtents) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveAllExtentsT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveAllExtentsT<i32[]>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveAllExtentsT<i32[][2]>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveAllExtentsT<i32[12][21]>, i32>));
}
