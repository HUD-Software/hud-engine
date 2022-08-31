#include <OSLayer/Traits/IsSwappable.h>

namespace {
    struct Moveable2;
    struct Moveable {
        Moveable(Moveable2&&);
    };
    struct Moveable2 {
        Moveable2(Moveable&&);
    };

    struct NotMoveable2;
    struct NotMoveable {
        NotMoveable(NotMoveable&&) = delete;
        NotMoveable(NotMoveable2&&) = delete;
        NotMoveable& operator=(NotMoveable&&) = delete;
    };
    struct NotMoveable2 {
        NotMoveable2(NotMoveable2&&) = delete;
        NotMoveable2& operator=(NotMoveable2&&) = delete;
    };
}

TEST(Traits, IsSwappable) {
    ASSERT_TRUE(hud::IsSwappableV<Moveable>);
    ASSERT_FALSE(hud::IsSwappableV<NotMoveable>);

    ASSERT_TRUE((hud::IsSwappableV<Moveable, Moveable2>));
    ASSERT_FALSE((hud::IsSwappableV<NotMoveable, NotMoveable2>));
}