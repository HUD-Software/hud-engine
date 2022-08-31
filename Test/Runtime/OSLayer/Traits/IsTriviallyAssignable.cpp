#include <OSLayer/Traits/IsTriviallyAssignable.h>

namespace{
    struct A { };
    struct B : A {};
    struct C { C& operator= (const A&) { return *this; } };
    struct D { D& operator= (const D&) { return *this; } };
}

TEST(Traits, IsTriviallyAssignable) {
    ASSERT_FALSE((hud::IsTriviallyAssignableV<i32, i32>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<i32&, i32>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<i32[32], i32[32]>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<i32*, i32*>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<A, A>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<A, B>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<A, B&>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<A, B&&>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<A, C>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<A, D>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<B, A>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<B, B>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<B, C>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<B, D>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<C, A>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<C, B>));
    ASSERT_TRUE((hud::IsTriviallyAssignableV<C, C&>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<C, D>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<D, A>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<D, B>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<D, C>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<D, D&>));
    ASSERT_FALSE((hud::IsTriviallyAssignableV<D, D&&>));
}