#include <OSLayer/Traits/RemoveConst.h>

TEST(Traits, RemoveConst) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<const i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<volatile i32>, volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<const volatile i32>, volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<const i32* const>, const i32*>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveConstT<const volatile i32* const volatile>, const volatile i32* volatile>));
}