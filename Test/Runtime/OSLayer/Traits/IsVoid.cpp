#include <OSLayer/Traits/IsVoid.h>

namespace {
    class A {};
}

TEST(Traits, IsVoid) {
    ASSERT_FALSE((hud::IsVoidV<i32>));
    ASSERT_FALSE((hud::IsVoidV<i32&>));
    ASSERT_FALSE((hud::IsVoidV<i32[]>));
    ASSERT_FALSE((hud::IsVoidV<i32[32]>));
    ASSERT_FALSE((hud::IsVoidV<i32*>));

    ASSERT_TRUE((hud::IsVoidV<void>));
    ASSERT_TRUE((hud::IsVoidV<const void>));
    ASSERT_TRUE((hud::IsVoidV<volatile void>));
    ASSERT_TRUE((hud::IsVoidV<const volatile void>));
    ASSERT_TRUE((hud::IsVoidV<hud::VoidT<>>));
    ASSERT_TRUE((hud::IsVoidV<const hud::VoidT<>>));
    ASSERT_TRUE((hud::IsVoidV<volatile hud::VoidT<>>));
    ASSERT_TRUE((hud::IsVoidV<const volatile hud::VoidT<>>));
    ASSERT_TRUE((hud::IsVoidV<decltype(void())>));
    ASSERT_FALSE((hud::IsVoidV<A>));
}
