#include <OSLayer/Traits/IsBitwiseCopyAssignable.h>

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

TEST(Traits, IsBitwiseCopyAssignable)
{
    // i8
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u8, uptr>));


    // i16
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u16, uptr>));


    // i32
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, i32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<char32, uptr>));
#endif
    // f32
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, char32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, f32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<f64, uptr>));

    // iptr
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<uptr, uptr>));

   

    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<Comp_Enum3, Comp_Enum4>));

    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32&, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<i32[32], i32[32]>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<i32*, i32*>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<A, A>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<A, B>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<A, C>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<A, D>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<B, A>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<B, B>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<B, C>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<B, D>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<C, A>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<C, B>));
    ASSERT_TRUE((hud::IsBitwiseCopyAssignableV<C, C>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<C, D>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<D, A>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<D, B>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<D, C>));
    ASSERT_FALSE((hud::IsBitwiseCopyAssignableV<D, D>));
}