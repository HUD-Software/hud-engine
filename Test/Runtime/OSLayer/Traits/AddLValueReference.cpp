#include <OSLayer/Traits/AddLValueReference.h>

TEST(Traits, AddLValueReference) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddLValueReferenceT<i32>, i32&>));
    ASSERT_TRUE((IsSameV<AddLValueReferenceT<i32&>, i32&>));
    ASSERT_TRUE((IsSameV<AddLValueReferenceT<i32&&>, i32&>));
    ASSERT_TRUE((IsSameV<AddLValueReferenceT<i32*>, i32*&>));
}