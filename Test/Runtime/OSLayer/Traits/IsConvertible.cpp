#include <OSLayer/Traits/IsConvertible.h>

namespace{
    struct A {};
    struct B {};
    struct C : public A { };
}

TEST(Traits, IsConvertible) {
    ASSERT_TRUE((hud::IsConvertibleV<i32, i32>));
    ASSERT_TRUE((hud::IsConvertibleV<i32, const i32>));
    ASSERT_TRUE((hud::IsConvertibleV<i32, const volatile i32>));
    ASSERT_TRUE((hud::IsConvertibleV<i32, f32>));
    ASSERT_TRUE((hud::IsConvertibleV<C, A>));
    ASSERT_TRUE((hud::IsConvertibleV<C, const A>));
    ASSERT_TRUE((hud::IsConvertibleV<C, const volatile A>));
    ASSERT_FALSE((hud::IsConvertibleV<A, C>));
    ASSERT_FALSE((hud::IsConvertibleV<B, A>));

    ASSERT_TRUE((hud::IsConvertibleV<C*, A*>)); // A* ptr = new C is valid
    ASSERT_TRUE((hud::IsConvertibleV<A(*)[], const A(*)[]>)); // Array-to-pointer is only convertible if same type with CV ( const A (*)[] = declval(A (*)[]) )
    ASSERT_FALSE((hud::IsConvertibleV<const A(*)[], A(*)[]>)); // Here we loose const, this is not convertible
    ASSERT_FALSE((hud::IsConvertibleV<A*, C*>)); // C* ptr = new A is not valid
}