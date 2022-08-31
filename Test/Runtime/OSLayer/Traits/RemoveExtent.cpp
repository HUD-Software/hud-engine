#include <OSLayer/Traits/RemoveExtent.h>

TEST(Traits, RemoveExtent) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveExtentT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveExtentT<i32[]>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveExtentT<i32[10]>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveExtentT<i32[][10]>, i32[10]>));
}