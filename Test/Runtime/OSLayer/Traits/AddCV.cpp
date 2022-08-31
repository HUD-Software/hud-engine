#include <OSLayer/Traits/AddCV.h>

TEST(Traits, AddCV) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<AddCVT<i32>, const volatile i32>));
    ASSERT_TRUE((IsSameV<AddCVT<const i32>, const volatile i32>));
    ASSERT_TRUE((IsSameV<AddCVT<volatile i32>, const volatile i32>));
    ASSERT_TRUE((IsSameV<AddCVT<i32*>, i32* const volatile>));
    ASSERT_TRUE((IsSameV<AddCVT<i32* volatile>, i32* const volatile>));
    ASSERT_TRUE((IsSameV<AddCVT<i32* const>, i32* const volatile>));
}