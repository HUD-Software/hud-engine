#include <OSLayer/Traits/IsStandardLayout.h>

namespace {
    struct A { int m; };
    struct B { int m1; private: [[maybe_unused]] int m2; };
    struct C { virtual void foo() {}; };
    struct D : A { int j; };
    struct E { int m; short a; int b; };
}

TEST(Traits, IsStandardLayout) {
    ASSERT_TRUE((hud::IsStandardLayoutV<A>));
    ASSERT_TRUE((hud::IsStandardLayoutV<i32>));
    ASSERT_TRUE((hud::IsStandardLayoutV<i32[]>));
    ASSERT_TRUE((hud::IsStandardLayoutV<i32[3]>));
    ASSERT_TRUE((hud::IsStandardLayoutV<i32*>));
    ASSERT_FALSE((hud::IsStandardLayoutV<B>));
    ASSERT_FALSE((hud::IsStandardLayoutV<C>));
    ASSERT_FALSE((hud::IsStandardLayoutV<D>));
    ASSERT_TRUE((hud::IsStandardLayoutV<E>));
}
