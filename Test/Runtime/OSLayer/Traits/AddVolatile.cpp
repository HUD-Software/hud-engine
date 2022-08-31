#include <OSLayer/Traits/AddVolatile.h>

TEST(Traits, AddVolatile) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddVolatileT<i32>, volatile i32>));
    ASSERT_TRUE((IsSameV<AddVolatileT<const i32>, const volatile i32>));
    ASSERT_TRUE((IsSameV<AddVolatileT<volatile i32>, volatile i32>));
    ASSERT_TRUE((IsSameV<AddVolatileT<i32*>, i32* volatile>));
    ASSERT_TRUE((IsSameV<AddVolatileT<i32* volatile>, i32* volatile>));
}