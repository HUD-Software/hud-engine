#include <OSLayer/Traits/IsNothrowSwappable.h>

namespace {
    struct Moveable2;
    struct Moveable {
        Moveable(Moveable&&);
        Moveable(Moveable2&&);
    };
    struct Moveable2 {
        Moveable2(Moveable&&);
        Moveable2(Moveable2&&);
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


    struct NothrowMoveable2;
    struct NothrowMoveable {
        NothrowMoveable(NothrowMoveable2&&) noexcept;
    };
    struct NothrowMoveable2 {
        NothrowMoveable2(NothrowMoveable&&) noexcept;
    };

    struct NothrowNotMoveable2;
    struct NothrowNotMoveable {
        NothrowNotMoveable(NothrowNotMoveable&&) noexcept = delete;
        NothrowNotMoveable(NothrowNotMoveable2&&) noexcept = delete;
        NothrowNotMoveable& operator=(NothrowNotMoveable&&) noexcept = delete;
    };
    struct NothrowNotMoveable2 {
        NothrowNotMoveable2(NothrowNotMoveable2&&) noexcept = delete;
        NothrowNotMoveable2& operator=(NothrowNotMoveable2&&) noexcept = delete;
    };
}

TEST(Traits, IsNothrowSwappable) {
    ASSERT_FALSE(hud::IsNothrowSwappableV<Moveable>);
    ASSERT_FALSE(hud::IsNothrowSwappableV<NotMoveable>);

    ASSERT_FALSE((hud::IsNothrowSwappableV<Moveable, Moveable2>));
    ASSERT_FALSE((hud::IsNothrowSwappableV<NotMoveable, NotMoveable2>));


    ASSERT_TRUE(hud::IsNothrowSwappableV<NothrowMoveable>);
    ASSERT_FALSE(hud::IsNothrowSwappableV<NothrowNotMoveable>);

    ASSERT_TRUE((hud::IsNothrowSwappableV<NothrowMoveable, NothrowMoveable2>));
    ASSERT_FALSE((hud::IsNothrowSwappableV<NothrowNotMoveable, NothrowNotMoveable2>));
}