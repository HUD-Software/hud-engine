#include <OSLayer/Traits/IsNothrowDefaultConstructible.h>

namespace {
    struct A {
        A() noexcept {}
    };
    struct B {
        B() noexcept(false) {}
    };

    struct C {
        C() { throw 20; }
    };
    struct D {
        D() noexcept : c() {}
        C c;
    };
    struct E {
        E() : c() {}
        C c;
    };
}

TEST(Traits, IsNothrowDefaultConstructible) {    
    ASSERT_TRUE((hud::IsNothrowDefaultConstructibleV<A>));
    ASSERT_FALSE((hud::IsNothrowDefaultConstructibleV<B>));
    ASSERT_FALSE((hud::IsNothrowDefaultConstructibleV<C>));
    ASSERT_TRUE((hud::IsNothrowDefaultConstructibleV<D>));
    ASSERT_FALSE((hud::IsNothrowDefaultConstructibleV<E>));
}