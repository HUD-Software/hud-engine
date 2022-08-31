#include <OSLayer/Traits/Conditional.h>

TEST(Traits, Conditional) {
    using namespace hud;

    ASSERT_TRUE((ConditionalT<true, TrueType, FalseType>::Value));
    ASSERT_FALSE((ConditionalT<true, FalseType, TrueType>::Value));
    ASSERT_FALSE((ConditionalT<false, TrueType, FalseType>::Value));
    ASSERT_TRUE((ConditionalT<false, FalseType, TrueType>::Value));
}