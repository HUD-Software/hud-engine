#include <OSLayer/Traits/IsTrivial.h>

namespace {
    class A {};
    class B { B() {} };
    class C : B {};
    class D { virtual void fn() {} };
}

TEST(Traits, IsTrivial) {
    ASSERT_TRUE((hud::IsTrivialV<A>));
    ASSERT_FALSE((hud::IsTrivialV<B>));
    ASSERT_FALSE((hud::IsTrivialV<C>));
    ASSERT_FALSE((hud::IsTrivialV<D>));
}