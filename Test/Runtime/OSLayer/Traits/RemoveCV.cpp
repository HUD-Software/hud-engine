#include <OSLayer/Traits/RemoveCV.h>

TEST(Traits, RemoveCV) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<volatile i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<const i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<const volatile i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<const i32* const>, const i32*>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVT<const volatile i32* const volatile>, const volatile i32*>));
}
