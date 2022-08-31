#include <OSLayer/Traits/IsEnum.h>

namespace {
    enum A { first, second, third };       // unscoped enum (C-style)
    class B {};
    enum class C { alpha, beta, gamma };   // scoped enum (C++11-style)
}

TEST(Traits, IsEnum) {
    ASSERT_FALSE((hud::IsEnumV<i32>));
    ASSERT_TRUE((hud::IsEnumV<A>));
    ASSERT_FALSE((hud::IsEnumV<B>));
    ASSERT_TRUE((hud::IsEnumV<C>));
    ASSERT_TRUE((hud::IsEnumV<decltype(C::alpha)>));
}