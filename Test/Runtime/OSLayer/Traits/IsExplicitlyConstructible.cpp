#include <OSLayer/Traits/IsExplicitlyDefaultConstructible.h>

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

TEST(Traits, IsExplicitlyConstructible) {
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<Exp>));
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<Exp, i32>));
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<Exp, const Exp&>));
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<Exp, Exp&&>));

    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<NoExp>));
    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<NoExp, i32>));
    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<NoExp, const NoExp&>));
    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<NoExp, NoExp&&>));

    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<i32>));
    ASSERT_FALSE((hud::IsExplicitlyConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsExplicitlyConstructibleV<const volatile i32>));
}
