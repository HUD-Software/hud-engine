#include <OSLayer/Traits/IsNotSame.h>

namespace {
    typedef int integer_type;
    struct A { int x, y; };
    struct B { int x, y; };
    struct C : public A {};
    typedef A D;

    template<typename T>
    struct IsSame_D {};
}

TEST(Traits, IsNotSame) {
    ASSERT_TRUE((hud::IsNotSameV<i32, const i32>));
    ASSERT_FALSE((hud::IsNotSameV<i32, integer_type>));

    ASSERT_FALSE((hud::IsNotSameV<A, A>));
    ASSERT_TRUE((hud::IsNotSameV<const A, A>));
    ASSERT_TRUE((hud::IsNotSameV<volatile A, A>));
    ASSERT_TRUE((hud::IsNotSameV<const volatile A, A>));

    ASSERT_TRUE((hud::IsNotSameV<A, B>));
    ASSERT_TRUE((hud::IsNotSameV<A, C>));
    ASSERT_FALSE((hud::IsNotSameV<A, D>));
    ASSERT_FALSE((hud::IsNotSameV<C, C>));
    ASSERT_FALSE((hud::IsNotSameV<IsSame_D<A>, IsSame_D<A>>));
    ASSERT_TRUE((hud::IsNotSameV<IsSame_D<A>, IsSame_D<C>>));
    ASSERT_TRUE((hud::IsNotSameV<IsSame_D<A>, IsSame_D<B>>));
}