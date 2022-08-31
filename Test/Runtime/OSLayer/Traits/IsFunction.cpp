#include <OSLayer/Traits/IsFunction.h>

namespace {
    int IsFunction_a(int i) { return i; }
    template<typename>
    struct IsFunction_PM {};
    template<class T, class U>
    struct IsFunction_PM<U T::*> {
        using Type = U;
    };

    [[maybe_unused]] int(*b)(int) = IsFunction_a; // pointer to function
    [[maybe_unused]] struct C { int operator()(int i) { return i; } } c;  // function-like class
    struct D {
        int d(int i) { return i; }
        int d2(int i) const { return i; }
        int d3(int i) volatile { return i; }
        int d4(int i) const volatile { return i; }
        int d5;
    };
}

TEST(Traits, IsFunction) {
    ASSERT_TRUE((hud::IsFunctionV<decltype(IsFunction_a)>));
    ASSERT_FALSE((hud::IsFunctionV<decltype(b)>));
    ASSERT_FALSE((hud::IsFunctionV<decltype(c)>));
    ASSERT_FALSE((hud::IsFunctionV<C>));
    ASSERT_FALSE((hud::IsFunctionV<decltype(C())>));
    ASSERT_FALSE((hud::IsFunctionV<D>));
    ASSERT_TRUE((hud::IsFunctionV<IsFunction_PM<decltype(&D::d)>::Type>));
    ASSERT_TRUE((hud::IsFunctionV<IsFunction_PM<decltype(&D::d2)>::Type>));
    ASSERT_TRUE((hud::IsFunctionV<IsFunction_PM<decltype(&D::d3)>::Type>));
    ASSERT_TRUE((hud::IsFunctionV<IsFunction_PM<decltype(&D::d4)>::Type>));
    ASSERT_FALSE((hud::IsFunctionV<IsFunction_PM<decltype(&D::d5)>::Type>));
}