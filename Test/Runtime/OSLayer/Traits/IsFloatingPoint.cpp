#include <OSLayer/Traits/IsFloatingPoint.h>

TEST(Traits, IsFloatingPoint) {
    ASSERT_TRUE((hud::IsFloatingPointV<f32>));
    ASSERT_TRUE((hud::IsFloatingPointV<const f32>));
    ASSERT_TRUE((hud::IsFloatingPointV<const volatile f32>));
    ASSERT_TRUE((hud::IsFloatingPointV<f64>));
    ASSERT_TRUE((hud::IsFloatingPointV<const f64>));
    ASSERT_TRUE((hud::IsFloatingPointV<const volatile f64>));
    ASSERT_FALSE((hud::IsFloatingPointV<class A>));
}
