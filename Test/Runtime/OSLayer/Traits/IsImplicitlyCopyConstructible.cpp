#include <OSLayer/Traits/IsImplicitlyCopyConstructible.h>


namespace {
    struct NoExp {
        NoExp(const NoExp&) noexcept {};
    };
    struct Exp {
        explicit Exp(const Exp&) noexcept {};
    };
}

TEST(Traits, IsImplicitlyCopyConstructible) {
    ASSERT_FALSE((hud::IsImplicitlyCopyConstructibleV<Exp>));
    ASSERT_TRUE((hud::IsImplicitlyCopyConstructibleV<NoExp>));
    ASSERT_TRUE((hud::IsImplicitlyCopyConstructibleV<i32>));
    ASSERT_TRUE((hud::IsImplicitlyCopyConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsImplicitlyCopyConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsImplicitlyCopyConstructibleV<const volatile i32>));
}