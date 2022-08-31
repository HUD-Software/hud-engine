#include <OSLayer/Templates/Min.h>

TEST(Templates, min) {
    using namespace hud;

    ASSERT_TRUE(min(1, 12.0f) == 1);
    ASSERT_TRUE(min(12.0f, 1) == 1);
    ASSERT_TRUE(min(12.0f, 12.0f) == 12.0f);
}
