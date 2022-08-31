#include <OSLayer/Traits/AddConst.h>

TEST(Traits, AddConst){
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddConstT<i32>, const i32>));
    ASSERT_TRUE((IsSameV<AddConstT<const i32>, const i32>));
    ASSERT_TRUE((IsSameV<AddConstT<volatile i32>, const volatile i32>));
    ASSERT_TRUE((IsSameV<AddConstT<i32*>, i32* const>));
    ASSERT_TRUE((IsSameV<AddConstT<i32* volatile>, i32* const volatile>));
}