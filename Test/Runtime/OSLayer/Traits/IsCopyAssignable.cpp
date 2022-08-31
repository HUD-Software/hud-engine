#include <OSLayer/Traits/IsCopyAssignable.h>

namespace {
    struct B {};
    struct A {
        A& operator=(const B&) noexcept { return *this; }
    };
    struct C : public A {};
    struct D {
        D& operator=(const B&) noexcept { return *this; }
    };
}

TEST(Traits, IsCopyAssignable) {  

    ASSERT_TRUE((hud::IsCopyAssignableV<i32>));
    ASSERT_FALSE((hud::IsCopyAssignableV<const i32>));
    ASSERT_FALSE((hud::IsCopyAssignableV<const volatile i32>));

    ASSERT_TRUE((hud::IsCopyAssignableV<A>));
    ASSERT_FALSE((hud::IsCopyAssignableV<const A>));
    ASSERT_FALSE((hud::IsCopyAssignableV<const volatile A>));
    ASSERT_TRUE((hud::IsCopyAssignableV<C>)); // C = C compile
    ASSERT_TRUE((hud::IsCopyAssignableV<D>)); // D = D do not compile no operator =
    ASSERT_TRUE((hud::IsCopyAssignableV<A, B>));
    ASSERT_FALSE((hud::IsCopyAssignableV<A, D>));
}