#include <OSLayer/Traits/IsExplicitlyCopyConstructible.h>

namespace {
    struct NoExp {
        NoExp(const NoExp&) noexcept {};
    };
    struct Exp {
        explicit Exp(const Exp&) noexcept {};
    };
}

TEST(Traits, IsExplicitlyCopyConstructible) {
    ASSERT_TRUE((hud::IsExplicitlyCopyConstructibleV<Exp>));
    ASSERT_FALSE((hud::IsExplicitlyCopyConstructibleV<NoExp>));
    ASSERT_FALSE((hud::IsExplicitlyCopyConstructibleV<i32>));
    ASSERT_FALSE((hud::IsExplicitlyCopyConstructibleV<const i32>));
    ASSERT_FALSE((hud::IsExplicitlyCopyConstructibleV<volatile i32>));
    ASSERT_FALSE((hud::IsExplicitlyCopyConstructibleV<const volatile i32>));
}