#include <OSLayer/Traits/IsSigned.h>

namespace {
    struct A {};
    enum class E : i32 {};
}

TEST(Traits, IsSigned) {
    ASSERT_FALSE((hud::IsSignedV<bool>));
    ASSERT_TRUE((hud::IsSignedV<i8>));
    ASSERT_TRUE((hud::IsSignedV<i16>));
    ASSERT_TRUE((hud::IsSignedV<i32>));
    ASSERT_TRUE((hud::IsSignedV<i64>));
    ASSERT_TRUE((hud::IsSignedV<iptr>));
    ASSERT_TRUE((hud::IsSignedV<f32>));
    ASSERT_TRUE((hud::IsSignedV<f64>));

    ASSERT_FALSE((hud::IsSignedV<u8>));
    ASSERT_FALSE((hud::IsSignedV<u16>));
    ASSERT_FALSE((hud::IsSignedV<u32>));
    ASSERT_FALSE((hud::IsSignedV<u64>));
    ASSERT_FALSE((hud::IsSignedV<uptr>));

    ASSERT_TRUE((hud::IsSignedV<isize>));
    ASSERT_FALSE((hud::IsSignedV<usize>));
    ASSERT_FALSE((hud::IsSignedV<char16>));
    ASSERT_FALSE((hud::IsSignedV<char32>));
    ASSERT_TRUE((hud::IsSignedV<ansichar>));
    #if defined(HD_OS_WINDOWS)
    ASSERT_FALSE((hud::IsSignedV<wchar>));
    #else // HD_OS_LINUX
    ASSERT_TRUE((hud::IsSignedV<wchar>));
    #endif
    ASSERT_FALSE((hud::IsSignedV<A>));

    ASSERT_FALSE((hud::IsSignedV<const bool>));
    ASSERT_TRUE((hud::IsSignedV<const i8>));
    ASSERT_TRUE((hud::IsSignedV<const i16>));
    ASSERT_TRUE((hud::IsSignedV<const i32>));
    ASSERT_TRUE((hud::IsSignedV<const i64>));
    ASSERT_TRUE((hud::IsSignedV<const iptr>));
    ASSERT_TRUE((hud::IsSignedV<const f32>));
    ASSERT_TRUE((hud::IsSignedV<const f64>));

    ASSERT_FALSE((hud::IsSignedV<const u8>));
    ASSERT_FALSE((hud::IsSignedV<const u16>));
    ASSERT_FALSE((hud::IsSignedV<const u32>));
    ASSERT_FALSE((hud::IsSignedV<const u64>));
    ASSERT_FALSE((hud::IsSignedV<const uptr>));

    ASSERT_TRUE((hud::IsSignedV<const isize>));
    ASSERT_FALSE((hud::IsSignedV<const usize>));
    ASSERT_FALSE((hud::IsSignedV<const char16>));
    ASSERT_FALSE((hud::IsSignedV<const char32>));
    ASSERT_TRUE((hud::IsSignedV<const ansichar>));
    #if defined(HD_OS_WINDOWS)
    ASSERT_FALSE((hud::IsSignedV<const wchar>));
    #else // HD_OS_LINUX
    ASSERT_TRUE((hud::IsSignedV<const wchar>));
    #endif
    ASSERT_FALSE((hud::IsSignedV<const A>));

    ASSERT_FALSE((hud::IsSignedV<volatile bool>));
    ASSERT_TRUE((hud::IsSignedV<volatile i8>));
    ASSERT_TRUE((hud::IsSignedV<volatile i16>));
    ASSERT_TRUE((hud::IsSignedV<volatile i32>));
    ASSERT_TRUE((hud::IsSignedV<volatile i64>));
    ASSERT_TRUE((hud::IsSignedV<volatile iptr>));
    ASSERT_TRUE((hud::IsSignedV<volatile f32>));
    ASSERT_TRUE((hud::IsSignedV<volatile f64>));

    ASSERT_FALSE((hud::IsSignedV<volatile u8>));
    ASSERT_FALSE((hud::IsSignedV<volatile u16>));
    ASSERT_FALSE((hud::IsSignedV<volatile u32>));
    ASSERT_FALSE((hud::IsSignedV<volatile u64>));
    ASSERT_FALSE((hud::IsSignedV<volatile uptr>));

    ASSERT_TRUE((hud::IsSignedV<volatile isize>));
    ASSERT_FALSE((hud::IsSignedV<volatile usize>));
    ASSERT_FALSE((hud::IsSignedV<volatile char16>));
    ASSERT_FALSE((hud::IsSignedV<volatile char32>));
    ASSERT_TRUE((hud::IsSignedV<volatile ansichar>));
    #if defined(HD_OS_WINDOWS)
    ASSERT_FALSE((hud::IsSignedV<volatile wchar>));
    #else // HD_OS_LINUX
    ASSERT_TRUE((hud::IsSignedV<volatile wchar>));
    #endif
    ASSERT_FALSE((hud::IsSignedV<volatile A>));

    ASSERT_FALSE((hud::IsSignedV<const volatile bool>));
    ASSERT_TRUE((hud::IsSignedV<const volatile i8>));
    ASSERT_TRUE((hud::IsSignedV<const volatile i16>));
    ASSERT_TRUE((hud::IsSignedV<const volatile i32>));
    ASSERT_TRUE((hud::IsSignedV<const volatile i64>));
    ASSERT_TRUE((hud::IsSignedV<const volatile iptr>));
    ASSERT_TRUE((hud::IsSignedV<const volatile f32>));
    ASSERT_TRUE((hud::IsSignedV<const volatile f64>));

    ASSERT_FALSE((hud::IsSignedV<const volatile u8>));
    ASSERT_FALSE((hud::IsSignedV<const volatile u16>));
    ASSERT_FALSE((hud::IsSignedV<const volatile u32>));
    ASSERT_FALSE((hud::IsSignedV<const volatile u64>));
    ASSERT_FALSE((hud::IsSignedV<const volatile uptr>));

    ASSERT_TRUE((hud::IsSignedV<const volatile isize>));
    ASSERT_FALSE((hud::IsSignedV<const volatile usize>));
    ASSERT_FALSE((hud::IsSignedV<const volatile char16>));
    ASSERT_FALSE((hud::IsSignedV<const volatile char32>));
    ASSERT_TRUE((hud::IsSignedV<const volatile ansichar>));
    #if defined(HD_OS_WINDOWS)
    ASSERT_FALSE((hud::IsSignedV<const volatile wchar>));
    #else // HD_OS_LINUX
    ASSERT_TRUE((hud::IsSignedV<const volatile wchar>));
    #endif
    ASSERT_FALSE((hud::IsSignedV<const volatile A>));

    ASSERT_FALSE((hud::IsSignedV<E>));
}
