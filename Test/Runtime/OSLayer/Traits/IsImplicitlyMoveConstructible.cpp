#include <OSLayer/Traits/IsImplicitlyMoveConstructible.h>

namespace {
    struct NoExp {
        NoExp(NoExp&&) noexcept {};
    };
    struct Exp {
        explicit Exp(Exp&&) noexcept {};
    };
}

TEST(Traits, IsImplicitlyMoveConstructible) {
    ASSERT_FALSE((hud::IsImplicitlyMoveConstructibleV<Exp>));
    ASSERT_TRUE((hud::IsImplicitlyMoveConstructibleV<NoExp>));
    ASSERT_TRUE((hud::IsImplicitlyMoveConstructibleV<i32>));
    ASSERT_TRUE((hud::IsImplicitlyMoveConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsImplicitlyMoveConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsImplicitlyMoveConstructibleV<const volatile i32>));
}
