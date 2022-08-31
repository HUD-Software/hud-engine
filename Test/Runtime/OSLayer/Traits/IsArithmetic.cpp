#include <OSLayer/Traits/IsArithmetic.h>

namespace {
    enum A {};
    class B {};
}

TEST(Traits, IsArithmetic) {
    ASSERT_TRUE(hud::IsArithmeticV<bool>);
    ASSERT_TRUE(hud::IsArithmeticV<i8>);
    ASSERT_TRUE(hud::IsArithmeticV<i16>);
    ASSERT_TRUE(hud::IsArithmeticV<i32>);
    ASSERT_TRUE(hud::IsArithmeticV<i64>);
    ASSERT_TRUE(hud::IsArithmeticV<u8>);
    ASSERT_TRUE(hud::IsArithmeticV<u16>);
    ASSERT_TRUE(hud::IsArithmeticV<u32>);
    ASSERT_TRUE(hud::IsArithmeticV<u64>);
    ASSERT_TRUE(hud::IsArithmeticV<ansichar>);
    ASSERT_TRUE(hud::IsArithmeticV<wchar>);
    ASSERT_TRUE(hud::IsArithmeticV<char16>);
    ASSERT_TRUE(hud::IsArithmeticV<char32>);
    ASSERT_FALSE(hud::IsArithmeticV<A>);
    ASSERT_FALSE(hud::IsArithmeticV<B>);
}