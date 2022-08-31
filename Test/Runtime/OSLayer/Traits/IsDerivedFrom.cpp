#include <OSLayer/Traits/IsDerivedFrom.h>

namespace {
    struct A {};
    struct B : public A {};
}

TEST(Traits, IsDerivedFrom) {
    ASSERT_FALSE((hud::IsDerivedFromV<A, A>));
    ASSERT_FALSE((hud::IsDerivedFromV<A, B>));
    ASSERT_TRUE((hud::IsDerivedFromV<B, A>));
    ASSERT_FALSE((hud::IsDerivedFromV<B, B>));
}
