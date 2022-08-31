#include <OSLayer/Traits/IsAnyTypeIn.h>

TEST(Traits, IsAnyOf) {
    ASSERT_TRUE((hud::IsAnyTypeInV<bool, int, long, float, short, bool, wchar_t>));
    ASSERT_TRUE((hud::IsAnyTypeInV<int, int, long, float, short, bool, wchar_t>));
    ASSERT_TRUE((hud::IsAnyTypeInV<wchar_t, int, long, float, short, bool, wchar_t>));
    ASSERT_FALSE((hud::IsAnyTypeInV<bool, int, long, float, short, wchar_t>));
}