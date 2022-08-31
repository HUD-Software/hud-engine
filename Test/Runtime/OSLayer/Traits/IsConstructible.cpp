#include <OSLayer/Traits/IsConstructible.h>

namespace {
    struct A {
        i32 a;
    };
    struct B {
        B(i32 b) : mB(b) {}
        i32 mB;
    };
    struct C {
        A a;
    };
    struct D {
        D(B b) : mB(b) {}
        B mB;
    };
    struct E {
        E() = default;
        E(A a) :mA(a) {}
        A mA;
    };
}
TEST(Traits, IsConstructible) {
    ASSERT_TRUE((hud::IsConstructibleV<A>));
#if defined(HD_COMPILER_CLANG_CL) || defined(HD_COMPILER_CLANG)
    // Bug: Waiting for clang anwser https://github.com/llvm/llvm-project/issues/55974
    // Clang do not implement the Parenthesized initialization of aggregates feature yet
    ASSERT_FALSE((hud::IsConstructibleV < A, i32 >));
#else
    ASSERT_TRUE((hud::IsConstructibleV < A, i32 >));
#endif
    ASSERT_FALSE((hud::IsConstructibleV<B>));
    ASSERT_TRUE((hud::IsConstructibleV<B, i32>));
    ASSERT_TRUE((hud::IsConstructibleV<B, const i32>));
    ASSERT_TRUE((hud::IsConstructibleV<B, const volatile i32>));
    ASSERT_TRUE((hud::IsConstructibleV<B, f32>)); // Implicit conversion f32 to i32
    ASSERT_TRUE((hud::IsConstructibleV<C>));
#if defined(HD_COMPILER_CLANG_CL) || defined(HD_COMPILER_CLANG)
// Bug: Waiting for clang anwser https://github.com/llvm/llvm-project/issues/55974
// Clang do not implement the Parenthesized initialization of aggregates feature yet
    ASSERT_FALSE((hud::IsConstructibleV<C, A>));
#else
    ASSERT_TRUE((hud::IsConstructibleV<C, A>));
#endif
    ASSERT_FALSE((hud::IsConstructibleV<D>)); // B Don't have default constructor
    ASSERT_TRUE((hud::IsConstructibleV<D, B>));
    ASSERT_TRUE((hud::IsConstructibleV<D, i32>)); // B is create with i32
    ASSERT_TRUE((hud::IsConstructibleV<E>));
    ASSERT_TRUE((hud::IsConstructibleV<E, A>));
}
