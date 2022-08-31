#include <OSLayer/Templates/BitCast.h>

TEST(Templates, bit_cast) {
    using namespace hud;

    constexpr f64 f64v = 19880124.0;
    constexpr auto u64v = bit_cast<u64>(f64v);
    ASSERT_EQ(bit_cast<f64>(u64v), f64v);

    constexpr u64 u64v2 = 0x3fe9000000000000ull;
    constexpr auto f64v2 = bit_cast<f64>(u64v2);
    ASSERT_EQ(bit_cast<u64>(f64v2), u64v2);
}