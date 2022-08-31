#include <OSLayer/Traits/IsNullptr.h>

namespace {
    [[maybe_unused]] int* a = 0;
}

TEST(Traits, IsNullptr) {
    ASSERT_FALSE((hud::IsNullptrV<decltype(a)>));
    ASSERT_FALSE((hud::IsNullptrV<decltype(0)>));
    ASSERT_FALSE((hud::IsNullptrV<decltype(&(*a))>));
    ASSERT_TRUE((hud::IsNullptrV<decltype(nullptr)>));
    ASSERT_TRUE((hud::IsNullptrV<std::nullptr_t>));
    ASSERT_TRUE((hud::IsNullptrV<hud::ptr::null>));
}