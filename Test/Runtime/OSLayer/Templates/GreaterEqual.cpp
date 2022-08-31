#include <OSLayer/Templates/GreaterEqual.h>

namespace {
    struct S {
        constexpr S(i32 val) noexcept
            : value(val) {
        }

        constexpr bool operator>=(const S& other) const noexcept {
            return value >= other.value;
        }

        i32 value;
    };
}


TEST(Templates, greater_equal) {
    using namespace hud;

    GreaterEqual<i32> gr;
    ASSERT_TRUE(gr(2, 1));
    ASSERT_TRUE(gr(1, 1));
    ASSERT_FALSE(gr(1, 2));

    GreaterEqual<S> gr_s;
    ASSERT_TRUE(gr_s(S{ 2 }, S{ 1 }));
    ASSERT_TRUE(gr_s(S{ 1 }, S{ 1 }));
    ASSERT_FALSE(gr_s(S{ 1 }, S{ 2 }));

    GreaterEqual<i32*> gr_ptr;
    ASSERT_TRUE(gr_ptr(nullptr, nullptr));
    ASSERT_FALSE(gr_ptr(nullptr, reinterpret_cast<i32*>(0x1)));
    ASSERT_TRUE(gr_ptr(reinterpret_cast<i32*>(0x1), nullptr));
}