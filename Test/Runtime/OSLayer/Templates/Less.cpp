#include <OSLayer/Templates/Less.h>

namespace {
    struct S {
        constexpr S(i32 val) noexcept
            : value(val) {
        }

        constexpr bool operator<(const S& other) const noexcept {
            return value < other.value;
        }

        i32 value;
    };
}


TEST(Templates, less) {
    using namespace hud;

    Less<i32> ls;
    ASSERT_FALSE(ls(2, 1));
    ASSERT_FALSE(ls(1, 1));
    ASSERT_TRUE(ls(1, 2));

    Less<S> ls_s;
    ASSERT_FALSE(ls_s(S{ 2 }, S{ 1 }));
    ASSERT_FALSE(ls_s(S{ 1 }, S{ 1 }));
    ASSERT_TRUE(ls_s(S{ 1 }, S{ 2 }));

    Less<i32*> ls_ptr;
    ASSERT_FALSE(ls_ptr(nullptr, nullptr));
    ASSERT_TRUE(ls_ptr(nullptr, reinterpret_cast<i32*>(0x1)));
    ASSERT_FALSE(ls_ptr(reinterpret_cast<i32*>(0x1), nullptr));
}