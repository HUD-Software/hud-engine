#include <OSLayer/Traits/IsMemberPointer.h>

namespace {
    [[maybe_unused]] int i = 0;
    [[maybe_unused]] const int i1 = 0;
    [[maybe_unused]] volatile int i2 = 0;
    [[maybe_unused]] const volatile int i3 = 0;
    struct A {
        void fn_a() {};
        void fn_a2() const {};
        void fn_a3() volatile {};
        void fn_a4() const volatile {};
        int a = 0;
        const int a1 = 0;
        volatile int a2 = 0;
        const volatile int a3 = 0;
    };
    [[maybe_unused]] void(A::* pt)() = &A::fn_a;
    [[maybe_unused]] void(A::* pt2)() const = &A::fn_a2;
    [[maybe_unused]] void(A::* pt3)() volatile = &A::fn_a3;
    [[maybe_unused]] void(A::* pt4)() const volatile = &A::fn_a4;

    [[maybe_unused]] int IsFunction_a() { return 0; }
}

TEST(Traits, IsMemberPointer) {
    ASSERT_FALSE((hud::IsMemberPointerV<A*>));
    ASSERT_FALSE((hud::IsMemberPointerV<decltype(&i)>));
    ASSERT_FALSE((hud::IsMemberPointerV<decltype(&i1)>));
    ASSERT_FALSE((hud::IsMemberPointerV<decltype(&i2)>));
    ASSERT_FALSE((hud::IsMemberPointerV<decltype(&i3)>));
    ASSERT_TRUE((hud::IsMemberPointerV<void(A::*)()>));
    ASSERT_TRUE((hud::IsMemberPointerV<void(A::*)()const>));
    ASSERT_TRUE((hud::IsMemberPointerV<void(A::*)()volatile>));
    ASSERT_TRUE((hud::IsMemberPointerV<void(A::*)()const volatile>));
    ASSERT_FALSE((hud::IsMemberPointerV<decltype(&IsFunction_a)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::fn_a)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::fn_a2)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::fn_a3)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::fn_a4)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::a)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::a1)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::a2)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(&A::a3)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(pt)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(pt2)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(pt3)>));
    ASSERT_TRUE((hud::IsMemberPointerV<decltype(pt4)>));
}