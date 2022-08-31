#include <OSLayer/Traits/IsCopyConstructible.h>

namespace {
    struct A { };
    struct B { B(B&&) noexcept {} };
    struct C { C(const C&) noexcept {} };
    struct D { D(const C&) noexcept {} };
}

TEST(Traits, IsCopyConstructible) {
    ASSERT_TRUE((hud::IsCopyConstructibleV<i32>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<i32&>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<const i32>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<const volatile i32>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<A>));
    ASSERT_FALSE((hud::IsCopyConstructibleV<B>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<C>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<D, C>));
    ASSERT_TRUE((hud::IsCopyConstructibleV<D, D>));
    ASSERT_FALSE((hud::IsCopyConstructibleV<D, B>));
}