#include <OSLayer/Traits/VoidT.h>

TEST(Traits, VoidType) {
    ASSERT_TRUE((hud::IsSameV<hud::VoidT<>, void>));
}