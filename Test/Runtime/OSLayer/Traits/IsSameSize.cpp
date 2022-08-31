#include <OSLayer/Traits/IsSameSize.h>

namespace {
    struct A {};
    struct B {
        i32 a;
    };
    struct C {
        i64 a;
    };
    struct D {
        f32 a;
    };
}

TEST(Traits, IsSameSize) {
    ASSERT_TRUE((hud::IsSameSizeV<i32, const i32>));
    ASSERT_TRUE((hud::IsSameSizeV<A, std::tuple<>>)); // Change for Tuple and IsTrue
    ASSERT_FALSE((hud::IsSameSizeV<A, B>));
    ASSERT_FALSE((hud::IsSameSizeV<B, C>));
    ASSERT_TRUE((hud::IsSameSizeV<B, D>));
    ASSERT_TRUE((hud::IsSameSizeV<B, i32>));
    ASSERT_TRUE((hud::IsSameSizeV<B[2], i32[1]>));
}