#include <OSLayer/Traits/IsBitwiseMoveConstructible.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A { };
    struct B { B(B&&) noexcept {} };
    struct C { virtual void fn() {} };
}

TEST(Traits, IsBitwiseMoveConstructible) {
    // i8
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u8, uptr>));


    // i16
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u16, uptr>));


    // i32
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, i32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<char32, uptr>));
#endif
    // f32
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, char32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, f32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<f64, uptr>));

    // iptr
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<uptr, uptr>));

    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<Comp_Enum3, Comp_Enum4>));

    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32&, i32&>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<i32[32], i32[32]>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32*, i32*>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32*, u32*>));
    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<i32*, u8*>));

    ASSERT_TRUE((hud::IsBitwiseMoveConstructibleV<A, A>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<B, B>));
    ASSERT_FALSE((hud::IsBitwiseMoveConstructibleV<C, C>));
}