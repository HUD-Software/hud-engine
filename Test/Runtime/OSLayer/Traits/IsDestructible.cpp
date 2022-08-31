#include <OSLayer/Traits/IsDestructible.h>

#if defined(HD_OS_WINDOWS)
#pragma warning(disable:4624) // 'derived class' : destructor was implicitly defined as deleted because a base class destructor is inaccessible or deleted
#endif

namespace {
    struct A { };
    struct B { virtual ~B() = delete; };
    struct C : B { };
    struct D { ~D() noexcept {} };
}

TEST(Traits, IsDestructible) {
    ASSERT_TRUE((hud::IsDestructibleV<i32>));
    ASSERT_TRUE((hud::IsDestructibleV<i32&>));
    ASSERT_TRUE((hud::IsDestructibleV<i32&&>));
    ASSERT_TRUE((hud::IsDestructibleV<volatile i32>));
    ASSERT_TRUE((hud::IsDestructibleV<const i32>));
    ASSERT_TRUE((hud::IsDestructibleV<const volatile i32>));
    ASSERT_TRUE((hud::IsDestructibleV<A>));
    ASSERT_FALSE((hud::IsDestructibleV<B>));
    ASSERT_FALSE((hud::IsDestructibleV<C>));
    ASSERT_FALSE((hud::IsDestructibleV<void>));
    ASSERT_FALSE((hud::IsDestructibleV<const void>));
    ASSERT_FALSE((hud::IsDestructibleV<volatile void>));
    ASSERT_FALSE((hud::IsDestructibleV<const volatile void>));
    ASSERT_FALSE((hud::IsDestructibleV<i32[]>));
    ASSERT_FALSE((hud::IsDestructibleV<const i32[]>));
    ASSERT_FALSE((hud::IsDestructibleV<volatile i32[]>));
    ASSERT_FALSE((hud::IsDestructibleV<const volatile i32[]>));

}