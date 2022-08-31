#include <OSLayer/Traits/IsImplicitlyDefaultConstructible.h>


namespace {
    struct NoExp {
        NoExp() noexcept {};
    };
    struct Exp {
        explicit Exp() noexcept {}
    };
}

TEST(Traits, IsImplicitlyDefaultConstructible) {
    ASSERT_FALSE((hud::IsImplicitlyDefaultConstructibleV<Exp>));
    ASSERT_TRUE((hud::IsImplicitlyDefaultConstructibleV<NoExp>));
    ASSERT_TRUE((hud::IsImplicitlyDefaultConstructibleV<i32>));
    ASSERT_TRUE((hud::IsImplicitlyDefaultConstructibleV<const i32>));
    ASSERT_FALSE((hud::IsImplicitlyDefaultConstructibleV<volatile i32>));
    ASSERT_FALSE((hud::IsImplicitlyDefaultConstructibleV<const volatile i32>));
}
