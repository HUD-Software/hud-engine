#include <OSLayer/Traits/IsNothrowCopyAssignable.h>

namespace {
    struct A { };
    struct B {
        B& operator= (const B&) { return *this; }
    };
    struct C {
        C& operator= (const C&) noexcept { return *this; }
        C& operator= (const B&) noexcept { return *this; }
        C& operator= (const A&) { return *this; }
    };
}

TEST(Traits, IsNothrowCopyAssignable) {   
    ASSERT_TRUE((hud::IsNothrowCopyAssignableV<i32>));
    ASSERT_TRUE((hud::IsNothrowCopyAssignableV<A>));
    ASSERT_FALSE((hud::IsNothrowCopyAssignableV<B>));
    ASSERT_TRUE((hud::IsNothrowCopyAssignableV<C>));
    ASSERT_TRUE((hud::IsNothrowCopyAssignableV<C, B>));
    ASSERT_FALSE((hud::IsNothrowCopyAssignableV<C, A>));
    ASSERT_FALSE((hud::IsNothrowCopyAssignableV<B, C>));

}