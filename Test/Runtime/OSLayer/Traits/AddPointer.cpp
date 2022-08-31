#include <OSLayer/Traits/AddPointer.h>

TEST(traits, AddPointer) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddPointerT<i32>, i32*>));
    ASSERT_TRUE((IsSameV<AddPointerT<i32&>, i32*>));
    ASSERT_TRUE((IsSameV<AddPointerT<i32&&>, i32*>));
    ASSERT_TRUE((IsSameV<AddPointerT<i32*>, i32**>));
}