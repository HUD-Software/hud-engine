#include <OSLayer/Traits/IsBitwiseMoveAssignable.h>

namespace {

    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A { };
    struct B { B& operator=(A&&) noexcept { return *this; } };
    struct C { C& operator=(C&&) noexcept { return *this; } };

}

TEST(Traits, IsBitwiseMoveAssignable) {
    // i8
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u8, uptr>));


    // i16
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, wchar>));
#endif 
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u16, uptr>));


    // i32
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, i32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<char32, uptr>));
#endif
    // f32
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, char32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, f32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<f64, uptr>));

    // iptr
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<uptr, uptr>));

    

    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<Comp_Enum3, Comp_Enum4>));


    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32, i32>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32&, i32&>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<i32[], i32[]>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV < i32[32], i32[32] >));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<i32*, i32*>));

    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<A, A>));
    ASSERT_TRUE((hud::IsBitwiseMoveAssignableV<B, B>));
    ASSERT_FALSE((hud::IsBitwiseMoveAssignableV<C, C>));
}