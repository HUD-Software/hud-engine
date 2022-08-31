#include <OSLayer/Templates/Declval.h>

TEST(Templates, declval) {
    using namespace hud;

    i32 integer = 22;
    decltype(declval<i32>()) n = move(integer);
    ASSERT_EQ(n, integer);
}