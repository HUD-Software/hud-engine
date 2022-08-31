#include <OSLayer/Templates/LessEqual.h>

namespace {
    struct S {
        constexpr S(i32 val) noexcept
            : value(val) {
        }

        constexpr bool operator<=(const S& other) const noexcept {
            return value <= other.value;
        }

        i32 value;
    };
}


TEST(Templates, less_equal) {
    using namespace hud;

    LessEqual<i32> le;
    ASSERT_FALSE(le(2, 1));
    ASSERT_TRUE(le(1, 1));
    ASSERT_TRUE(le(1, 2));

    LessEqual<S> le_s;
    ASSERT_FALSE(le_s(S{ 2 }, S{ 1 }));
    ASSERT_TRUE(le_s(S{ 1 }, S{ 1 }));
    ASSERT_TRUE(le_s(S{ 1 }, S{ 2 }));

    LessEqual<i32*> le_ptr;
    ASSERT_TRUE(le_ptr(nullptr, nullptr));
    ASSERT_TRUE(le_ptr(nullptr, reinterpret_cast<i32*>(0x1)));
    ASSERT_FALSE(le_ptr(reinterpret_cast<i32*>(0x1), nullptr));
}