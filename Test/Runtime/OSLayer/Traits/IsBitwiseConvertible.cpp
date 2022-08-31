#include <OSLayer/Traits/IsBitwiseConvertible.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A { };
    struct B : A {};
    struct C { C& operator= (const A&) { return *this; } };
    struct D { D& operator= (const D&) { return *this; } };
}

TEST(Traits, IsBitwiseConvertible) {
    // i8
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u8, uptr>));

    // i16
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u16, uptr>));

    // i32
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, i32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<char32, uptr>));
#endif

    // f32
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, char32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, f32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<f64, uptr>));


    // iptr
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<uptr, uptr>));

   

    ASSERT_TRUE((hud::IsBitwiseConvertibleV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<Comp_Enum3, Comp_Enum4>));

    

    ASSERT_TRUE((hud::IsBitwiseConvertibleV<A, A>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<A, B>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<A, C>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<A, D>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<B, A>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<B, B>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<B, C>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<B, D>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<C, A>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<C, B>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<C, C>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<C, D>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<D, A>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<D, B>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<D, C>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<D, D>));

    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseConvertibleV<i32&, i32>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32[], i32[]>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32[32], i32[32]>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32*, i32*>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32*, u32*>));
    ASSERT_TRUE((hud::IsBitwiseConvertibleV<i32*, u8*>));
}