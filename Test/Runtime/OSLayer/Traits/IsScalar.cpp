#include <OSLayer/Traits/IsScalar.h>

namespace {
    struct A { void fn() {} };
    enum class E {};
}

TEST(Traits, IsScalar) {
    ASSERT_FALSE((hud::IsScalarV<A>));
    ASSERT_TRUE((hud::IsScalarV<E>));
    ASSERT_TRUE((hud::IsScalarV<i8>));
    ASSERT_TRUE((hud::IsScalarV<i16>));
    ASSERT_TRUE((hud::IsScalarV<i32>));
    ASSERT_TRUE((hud::IsScalarV<i64>));
    ASSERT_TRUE((hud::IsScalarV<iptr>));
    ASSERT_TRUE((hud::IsScalarV<u8>));
    ASSERT_TRUE((hud::IsScalarV<u16>));
    ASSERT_TRUE((hud::IsScalarV<u32>));
    ASSERT_TRUE((hud::IsScalarV<u64>));
    ASSERT_TRUE((hud::IsScalarV<uptr>));
    ASSERT_TRUE((hud::IsScalarV<isize>));
    ASSERT_TRUE((hud::IsScalarV<usize>));
    ASSERT_TRUE((hud::IsScalarV<ansichar>));
    ASSERT_TRUE((hud::IsScalarV<wchar>));
    ASSERT_TRUE((hud::IsScalarV<A*>));
    ASSERT_TRUE((hud::IsScalarV<decltype(&A::fn)>));
    ASSERT_FALSE((hud::IsScalarV<int(int)>));
}