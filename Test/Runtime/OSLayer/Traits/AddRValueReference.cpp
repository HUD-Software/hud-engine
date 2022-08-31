#include <OSLayer/Traits/AddRValueReference.h>

TEST(Traits, AddRValueReference) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddRValueReferenceT<i32>, i32&&>));
    ASSERT_TRUE((IsSameV<AddRValueReferenceT<i32&>, i32&>));
    ASSERT_TRUE((IsSameV<AddRValueReferenceT<i32&&>, i32&&>));
    ASSERT_TRUE((IsSameV<AddRValueReferenceT<i32*>, i32*&&>));
}