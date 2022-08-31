#include <OSLayer/Traits/IsUnsigned.h>

namespace {
    struct A {};
}

TEST(Traits, IsUnsigned) {
    ASSERT_TRUE((hud::IsUnsignedV<bool>));
    ASSERT_FALSE((hud::IsUnsignedV<i8>));
    ASSERT_FALSE((hud::IsUnsignedV<i16>));
    ASSERT_FALSE((hud::IsUnsignedV<i32>));
    ASSERT_FALSE((hud::IsUnsignedV<i64>));
    ASSERT_FALSE((hud::IsUnsignedV<iptr>));
    ASSERT_FALSE((hud::IsUnsignedV<f32>));
    ASSERT_FALSE((hud::IsUnsignedV<f64>));

    ASSERT_TRUE((hud::IsUnsignedV<u8>));
    ASSERT_TRUE((hud::IsUnsignedV<u16>));
    ASSERT_TRUE((hud::IsUnsignedV<u32>));
    ASSERT_TRUE((hud::IsUnsignedV<u64>));
    ASSERT_TRUE((hud::IsUnsignedV<uptr>));

    ASSERT_FALSE((hud::IsUnsignedV<isize>));
    ASSERT_TRUE((hud::IsUnsignedV<usize>));
    ASSERT_TRUE((hud::IsUnsignedV<char16>));
    ASSERT_TRUE((hud::IsUnsignedV<char32>));
    ASSERT_FALSE((hud::IsUnsignedV<ansichar>));
    #if defined(HD_OS_WINDOWS)
    ASSERT_TRUE((hud::IsUnsignedV<wchar>));
    #else // HD_OS_LINUX
    ASSERT_FALSE((hud::IsUnsignedV<wchar>));
    #endif
    ASSERT_FALSE((hud::IsUnsignedV<A>));
}
