#include <OSLayer/Traits/IsBitwiseCopyConstructible.h>

namespace {

    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A { };
    struct B { B(const B&) {} };
    struct C { virtual void fn() {} };
    struct D { D(A&&) {} };

}

TEST(Traits, IsBitwiseCopyConstructible)
{
    // i8
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u8, uptr>));


    // i16
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u16, uptr>));


    // i32
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, i32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<char32, uptr>));
#endif
    // f32
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, char32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, f32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<f64, uptr>));

    // iptr
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<uptr, uptr>));


    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<Comp_Enum3, Comp_Enum4>));

    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32, i32>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32&, i32&>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<i32[32], i32[32]>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<i32*, i32*>));

    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<A, A>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<B, B>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<C, C>));
    ASSERT_TRUE((hud::IsBitwiseCopyConstructibleV<D, D>));
    ASSERT_FALSE((hud::IsBitwiseCopyConstructibleV<D, A>));
}