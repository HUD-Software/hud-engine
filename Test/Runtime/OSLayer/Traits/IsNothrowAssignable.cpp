#include <OSLayer/Traits/IsNothrowAssignable.h>

namespace {
    struct A { };
    struct B {
        B& operator= (const A&) noexcept { return *this; }
        B& operator= (const B&) { return *this; }
        B& operator= (A&&) noexcept { return *this; }
        B& operator= (B&&) { return *this; }
    };
}

TEST(Traits, IsNothrowAssignable) {
    ASSERT_TRUE((hud::IsNothrowAssignableV<A, A>));
    ASSERT_TRUE((hud::IsNothrowAssignableV<B, A&>));
    ASSERT_FALSE((hud::IsNothrowAssignableV<B, B&>));
    ASSERT_TRUE((hud::IsNothrowAssignableV<B, A&&>));
    ASSERT_FALSE((hud::IsNothrowAssignableV<B, B&&>));
}