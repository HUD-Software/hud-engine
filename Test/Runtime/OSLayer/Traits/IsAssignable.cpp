#include <OSLayer/Traits/IsAssignable.h>

namespace {
    struct A {};
    struct B {};
    struct C : public A {};
    struct D {
        D& operator=(const B&) { return *this; }
    };
}

TEST(Traits, IsAssignable) {
    
    ASSERT_FALSE((hud::IsAssignableV<i32, i32>)); // 1 = 1 do not compile
    ASSERT_TRUE((hud::IsAssignableV<i32&, i32>));
    ASSERT_TRUE((hud::IsAssignableV<i32&, const i32>));
    ASSERT_TRUE((hud::IsAssignableV<i32&, const volatile i32>));
    ASSERT_FALSE((hud::IsAssignableV<const i32&, i32>));
    ASSERT_FALSE((hud::IsAssignableV<const volatile i32&, const i32>));
    ASSERT_FALSE((hud::IsAssignableV<const i32&, const i32>));
    ASSERT_FALSE((hud::IsAssignableV<const volatile i32&, const volatile i32>));
    ASSERT_TRUE((hud::IsAssignableV<A, A>)); // A() = A() compile
    ASSERT_TRUE((hud::IsAssignableV<A&, A>)); // A a ; a = A() compile
    ASSERT_FALSE((hud::IsAssignableV<const A&, A>)); // const A a ; a = A() do not compile
    ASSERT_TRUE((hud::IsAssignableV<A, C>)); // A() = C() compile
    ASSERT_FALSE((hud::IsAssignableV<A, B>)); // A() = B() do not compile
    ASSERT_TRUE((hud::IsAssignableV<D, B>)); // D() = B() compile
}
