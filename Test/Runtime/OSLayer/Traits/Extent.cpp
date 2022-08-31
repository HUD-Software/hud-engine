#include <OSLayer/Traits/Extent.h>


TEST(Traits, Extent) {
    using namespace hud;

    ASSERT_EQ(ExtentV<i32>, 0u);
    ASSERT_EQ((ExtentV<i32, 1>), 0u);

    ASSERT_EQ(ExtentV<i32[]>, 0u);
    ASSERT_EQ((ExtentV<i32[], 1>), 0u);

    ASSERT_EQ(ExtentV<i32[][8]>, 0u);
    ASSERT_EQ((ExtentV<i32[][8], 1>), 8u);
    ASSERT_EQ((ExtentV<i32[][8], 2>), 0u);

    ASSERT_EQ(ExtentV<i32[][8][16]>, 0u);
    ASSERT_EQ((ExtentV<i32[][8][16], 1>), 8u);
    ASSERT_EQ((ExtentV<i32[][8][16], 2>), 16u);
    ASSERT_EQ((ExtentV<i32[][8][16], 3>), 0u);
}