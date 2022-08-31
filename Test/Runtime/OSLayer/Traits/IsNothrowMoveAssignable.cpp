#include <OSLayer/Traits/IsNothrowMoveAssignable.h>

namespace{
    struct A { };
    struct B {
        B& operator=(B&&) { return *this; }
    };
    struct C {
        C& operator=(C&&) noexcept { return *this; }
        C& operator=(A&&) noexcept { return *this; }
        C& operator=(B&&) { return *this; }
    };
}

TEST(Traits, IsNothrowMoveAssignable) {   
    ASSERT_TRUE((hud::IsNothrowMoveAssignableV<i32>));
    ASSERT_TRUE((hud::IsNothrowMoveAssignableV<A>));
    ASSERT_FALSE((hud::IsNothrowMoveAssignableV<B>));
    ASSERT_TRUE((hud::IsNothrowMoveAssignableV<C>));
    ASSERT_TRUE((hud::IsNothrowMoveAssignableV<C, A>));
    ASSERT_FALSE((hud::IsNothrowMoveAssignableV<C, B>));
}
