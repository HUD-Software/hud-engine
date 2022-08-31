#include <OSLayer/Traits/IsTriviallyCopyConstructible.h>

namespace {
    struct A { };
    struct B { B(const B&) {} };
    struct C { virtual void fn() {} };
    struct D { D(A&&) {} };
}

TEST(Traits, IsTriviallyCopyConstructible) {
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<i32>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyCopyConstructibleV<i32[]>));
    ASSERT_FALSE((hud::IsTriviallyCopyConstructibleV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<i32*>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<i32, f32>));

    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<A>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<A, A>));
    ASSERT_FALSE((hud::IsTriviallyCopyConstructibleV<B>));
    ASSERT_FALSE((hud::IsTriviallyCopyConstructibleV<C>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<D>));
    ASSERT_TRUE((hud::IsTriviallyCopyConstructibleV<D, D>));
    ASSERT_FALSE((hud::IsTriviallyCopyConstructibleV<D, A>));
}