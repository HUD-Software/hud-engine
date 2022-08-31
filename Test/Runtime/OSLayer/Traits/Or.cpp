#include <OSLayer/Traits/Or.h>

TEST(Traits, Or) {
    ASSERT_TRUE((hud::OrV<hud::TrueType, hud::TrueType>));
    ASSERT_TRUE((hud::OrV<hud::TrueType, hud::FalseType>));
    ASSERT_TRUE((hud::OrV<hud::FalseType, hud::TrueType>));
    ASSERT_FALSE((hud::OrV<hud::FalseType, hud::FalseType>));
}