#include <OSLayer/Traits/IsVolatile.h>

TEST(Traits, IsVolatile) {
    ASSERT_FALSE((hud::IsVolatileV<int>));
    ASSERT_TRUE((hud::IsVolatileV<volatile int>));
    ASSERT_FALSE((hud::IsVolatileV<const int>));
    ASSERT_TRUE((hud::IsVolatileV<const volatile int>));
    ASSERT_FALSE((hud::IsVolatileV<volatile int*>));
    ASSERT_TRUE((hud::IsVolatileV<volatile int* volatile>));
}
