#include <OSLayer/Traits/IsMoveAssignable.h>

namespace {
    struct A { };
    struct B { B& operator= (B&&) = delete; };
    struct C { C& operator= (B&&) noexcept { return *this; } };
}

TEST(Traits, IsMoveAssignable) {
    ASSERT_TRUE((hud::IsMoveAssignableV<i32>));
    ASSERT_TRUE((hud::IsMoveAssignableV<A>));
    ASSERT_FALSE((hud::IsMoveAssignableV<B>));
    ASSERT_TRUE((hud::IsMoveAssignableV<C, B>));
    ASSERT_FALSE((hud::IsMoveAssignableV<B, C>));
}