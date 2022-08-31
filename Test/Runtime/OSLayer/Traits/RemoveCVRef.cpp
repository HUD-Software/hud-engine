#include <OSLayer/Traits/RemoveCVRef.h>

TEST(Traits, RemoveCVRef) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<i32&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<volatile i32&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<const i32&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<const volatile i32&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<const i32* const&>, const i32*>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveCVRefT<const volatile i32* const volatile& >, const volatile i32*>));
}
