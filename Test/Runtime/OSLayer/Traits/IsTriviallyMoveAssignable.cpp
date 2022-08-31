#include <OSLayer/Traits/IsTriviallyMoveAssignable.h>

namespace {
    struct A { };
    struct B {
        B& operator=(A&&) noexcept { return *this; }
    };
    struct C {
        C& operator=(C&&) noexcept { return *this; }
    };
}

TEST(Traits, IsTriviallyMoveAssignable) {
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<i32>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<i32&>));
    ASSERT_FALSE((hud::IsTriviallyMoveAssignableV<i32[]>));
    ASSERT_FALSE((hud::IsTriviallyMoveAssignableV<i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<i32*>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<i32, f32>));

    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<A>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<A, A>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<B>));
    ASSERT_TRUE((hud::IsTriviallyMoveAssignableV<B, B>));
    ASSERT_FALSE((hud::IsTriviallyMoveAssignableV<C>));
}