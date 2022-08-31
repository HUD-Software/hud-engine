#include <OSLayer/Traits/IsExplicitlyDefaultConstructible.h>

namespace {
    struct NoExp {
        NoExp() noexcept {};
    };
    struct Exp {
        explicit Exp() noexcept {}
    };
}

TEST(Traits, IsExplicitlyDefaultConstructible) {
    ASSERT_TRUE((hud::IsExplicitlyDefaultConstructibleV<Exp>));
    ASSERT_FALSE((hud::IsExplicitlyDefaultConstructibleV<NoExp>));
    ASSERT_FALSE((hud::IsExplicitlyDefaultConstructibleV<i32>));
    ASSERT_FALSE((hud::IsExplicitlyDefaultConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsExplicitlyDefaultConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsExplicitlyDefaultConstructibleV<const volatile i32>));
}
