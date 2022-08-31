#include <OSLayer/Traits/IsSame.h>


namespace {
    typedef int integer_type;
    struct A { int x, y; };
    struct B { int x, y; };
    struct C : public A {};
    typedef A D;

    template<typename T>
    struct IsSame_D {};
}

TEST(Traits, IsSame) {
    ASSERT_FALSE((hud::IsSameV<i32, const i32>));
    ASSERT_TRUE((hud::IsSameV<i32, integer_type>));

    ASSERT_TRUE((hud::IsSameV<A, A>));
    ASSERT_FALSE((hud::IsSameV<const A, A>));
    ASSERT_FALSE((hud::IsSameV<volatile A, A>));
    ASSERT_FALSE((hud::IsSameV<const volatile A, A>));

    ASSERT_FALSE((hud::IsSameV<A, B>));
    ASSERT_FALSE((hud::IsSameV<A, C>));
    ASSERT_TRUE((hud::IsSameV<A, D>));
    ASSERT_TRUE((hud::IsSameV<C, C>));
    ASSERT_TRUE((hud::IsSameV<IsSame_D<A>, IsSame_D<A>>));
    ASSERT_FALSE((hud::IsSameV<IsSame_D<A>, IsSame_D<C>>));
    ASSERT_FALSE((hud::IsSameV<IsSame_D<A>, IsSame_D<B>>));
}