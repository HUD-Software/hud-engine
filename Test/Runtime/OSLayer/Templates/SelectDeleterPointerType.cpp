#include <OSLayer/Templates/SelectDeleterPointerType.h>
#include <OSLayer/Traits/IsSame.h>

namespace {
    struct DeleterNoPointerType {
    };
    struct DeleterPointerType {
        using PointerType = float*;
    };
}

TEST(Templates, selectDeleterPointerType)
{
    using namespace hud;

    ASSERT_TRUE( (IsSameV<SelectDeleterPointerTypeT<i32, DeleterNoPointerType>, i32*>) );
    ASSERT_FALSE((IsSameV<SelectDeleterPointerTypeT<i32, DeleterNoPointerType>, float*>));
    ASSERT_TRUE((IsSameV<SelectDeleterPointerTypeT<i32, DeleterPointerType>, float*>));
    ASSERT_FALSE((IsSameV<SelectDeleterPointerTypeT<i32, DeleterPointerType>, i32*>));
}