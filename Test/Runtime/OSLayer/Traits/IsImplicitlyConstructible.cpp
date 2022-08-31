#include <OSLayer/Traits/IsImplicitlyConstructible.h>

namespace {
    struct NoExp {
        NoExp() noexcept {}
        NoExp(i32) noexcept {}
        NoExp(const NoExp&) noexcept {}
        NoExp(NoExp&&) noexcept {}
    };
    struct Exp {
        explicit Exp() noexcept {}
        explicit Exp(i32) noexcept {}
        explicit Exp(const Exp&) noexcept {}
        explicit Exp(Exp&&) noexcept {}
    };
}

TEST(Traits, IsImplicitlyConstructible) {
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<Exp>));
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<Exp, i32>));
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<Exp, const Exp&>));
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<Exp, Exp&&>));

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<NoExp>));
    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<NoExp, i32>));
    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<NoExp, const NoExp&>));
    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<NoExp, NoExp&&>));

    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<i32>));
    ASSERT_TRUE((hud::IsImplicitlyConstructibleV<const i32>));
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<volatile i32>));
    ASSERT_FALSE((hud::IsImplicitlyConstructibleV<const volatile i32>));
}
