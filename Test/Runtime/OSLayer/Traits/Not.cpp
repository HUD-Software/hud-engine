#include <OSLayer/Traits/Not.h>


TEST(Traits, Not) {
    ASSERT_TRUE((hud::NotV<hud::IntegralConstant<bool, 0>>));
    ASSERT_FALSE((hud::NotV<hud::IntegralConstant<bool, 1>>));
    ASSERT_TRUE((hud::NotV<hud::IntegralConstant<bool, false>>));
    ASSERT_FALSE((hud::NotV<hud::IntegralConstant<bool, true>>));

    ASSERT_TRUE((hud::NotV<hud::BoolConstant<false>>));
    ASSERT_FALSE((hud::NotV<hud::BoolConstant<true>>));
    ASSERT_TRUE((hud::NotV<hud::FalseType>));
    ASSERT_FALSE((hud::NotV<hud::TrueType>));
}