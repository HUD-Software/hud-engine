#include <OSLayer/Traits/IsExplicitlyMoveConstructible.h>

namespace {
    struct NoExp {
        NoExp(NoExp&&) noexcept {};
    };
    struct Exp {
        explicit Exp(Exp&&) noexcept {};
    };
}

TEST(Traits, IsExplicitlyMoveConstructible) {
    ASSERT_TRUE((hud::IsExplicitlyMoveConstructibleV<Exp>));
    ASSERT_FALSE((hud::IsExplicitlyMoveConstructibleV<NoExp>));
    ASSERT_FALSE((hud::IsExplicitlyMoveConstructibleV<i32>));
    ASSERT_FALSE((hud::IsExplicitlyMoveConstructibleV<const i32>));
    ASSERT_FALSE((hud::IsExplicitlyMoveConstructibleV<volatile i32>));
    ASSERT_FALSE((hud::IsExplicitlyMoveConstructibleV<const volatile i32>));
}
