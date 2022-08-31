#include <OSLayer/Traits/IsBool.h>

TEST(Traits, IsBool) {
    ASSERT_TRUE(hud::IsBoolV<bool>);
    ASSERT_TRUE(hud::IsBoolV<const bool>);
    ASSERT_TRUE(hud::IsBoolV<volatile bool>);
    ASSERT_TRUE(hud::IsBoolV<const volatile bool>);
}