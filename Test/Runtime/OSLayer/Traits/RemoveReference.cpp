#include <OSLayer/Traits/RemoveReference.h>


TEST(Traits, RemoveReference) {
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32[]>, i32[]>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32[10]>, i32[10]>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32*>, i32*>));

    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<i32&&>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<const i32&>, const i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<volatile i32&>, volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<const volatile i32&>, const volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<const i32&&>, const i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<volatile i32&&>, volatile i32>));
    ASSERT_TRUE((hud::IsSameV<hud::RemoveReferenceT<const volatile i32&&>, const volatile i32>));
}