#include <OSLayer/Traits/RemovePointer.h>


TEST(Traits, RemovePointer) {
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32[]>, i32[]>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32[10]>, i32[10]>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32[][10]>, i32[][10]>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32* []>, i32* []>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32* [10]>, i32* [10]>));

    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32*>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32**>, i32*>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32* const>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32* volatile>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<i32* const volatile>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<const i32*>, const i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<volatile i32*>, volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemovePointerT<const volatile i32*>, const volatile i32>));
}