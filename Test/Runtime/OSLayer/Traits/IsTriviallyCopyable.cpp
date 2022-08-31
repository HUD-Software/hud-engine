#include <OSLayer/Traits/IsTriviallyCopyable.h>

namespace {
    struct A { int i; };
    struct B {
        int i, j;
        B(const B& x) : i(x.i), j(x.j) {};
    };
    struct C {
        int i, j;
        C(const A& x) : i(x.i), j(1) {};
    };
}

TEST(Traits, IsTriviallyCopyable) {
    ASSERT_TRUE((hud::IsTriviallyCopyableV<i32>));
    ASSERT_FALSE((hud::IsTriviallyCopyableV<i32&>));
    ASSERT_TRUE((hud::IsTriviallyCopyableV<i32[]>));
    ASSERT_TRUE((hud::IsTriviallyCopyableV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyCopyableV<i32*>));

    ASSERT_TRUE((hud::IsTriviallyCopyableV<A>));
    ASSERT_FALSE((hud::IsTriviallyCopyableV<B>));
    ASSERT_TRUE((hud::IsTriviallyCopyableV<C>));
}