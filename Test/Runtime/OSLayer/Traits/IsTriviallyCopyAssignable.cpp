#include <OSLayer/Traits/IsTriviallyCopyAssignable.h>

namespace {
    struct A { };
    struct B : A {};
    struct C { C& operator= (const A&) { return *this; } };
    struct D {
        D& operator= (const D&) { return *this; }
        D& operator= (const A&) { return *this; }
    };
}

TEST(Traits, IsTriviallyCopyAssignable) {
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<i32>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyCopyAssignableV<i32[]>));
    ASSERT_FALSE((hud::IsTriviallyCopyAssignableV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<i32*>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<i32, f32>));

    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<A>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<A, A>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<B>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<B, B>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<C>));
    ASSERT_TRUE((hud::IsTriviallyCopyAssignableV<C, C>));
    ASSERT_FALSE((hud::IsTriviallyCopyAssignableV<D>));
    ASSERT_FALSE((hud::IsTriviallyCopyAssignableV<D, A>));
}
