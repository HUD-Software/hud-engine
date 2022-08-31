#include <OSLayer/Templates/Max.h>

TEST(Templates, max) {
    using namespace hud;

    ASSERT_TRUE(max(1, 12.0f) == 12.0f);
    ASSERT_TRUE(max(12.0f, 1) == 12.0f);
    ASSERT_TRUE(max(12.0f, 12.0f) == 12.0f);
}
