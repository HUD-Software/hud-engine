#include <OSLayer/Traits/IsTriviallyConstructible.h>

namespace {
    struct A { };
    struct B { B() {} };  // non-trivial default ctor.
    struct C : A { };
}

TEST(Traits, IsTriviallyConstructible) {
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<i32, i32>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<i32&, i32>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<i32[32], i32[32]>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<i32*, i32*>));

    ASSERT_TRUE((hud::IsTriviallyConstructibleV<A>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<A, A>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<A, A&>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<A, A&&>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<A, B>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<A, C>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<B>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<B, A>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<B, A&>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<B, A&&>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<B, B>));
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<B, C>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<C>));
#if defined(HD_COMPILER_CLANG_CL) || defined(HD_COMPILER_CLANG)
    // Bug: Waiting for clang anwser https://github.com/llvm/llvm-project/issues/55974
    // Clang do not implement the Parenthesized initialization of aggregates feature yet
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<C, A>));
#else
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<C, A>));
#endif
    ASSERT_FALSE((hud::IsTriviallyConstructibleV<C, B>));
    ASSERT_TRUE((hud::IsTriviallyConstructibleV<C, C>));
}