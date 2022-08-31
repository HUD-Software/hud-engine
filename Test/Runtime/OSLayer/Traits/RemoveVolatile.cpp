#include <OSLayer/Traits/RemoveVolatile.h>

TEST(Traits, RemoveVolatile) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<const i32>, const i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<volatile i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<const volatile i32>, const i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<const i32* const>, const i32* const>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveVolatileT<const volatile i32* const volatile>, const volatile i32* const>));
}