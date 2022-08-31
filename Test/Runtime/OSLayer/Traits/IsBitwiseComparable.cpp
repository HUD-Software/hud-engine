#include <OSLayer/Traits/IsBitwiseComparable.h>

namespace {
    struct Empty {};
    struct A {
        i32 a;
    };
    struct B {
        i32 a;
        f32 f;
    };
    struct C {
        i32 a;
        i16 f;
        i16 g;
    };
    struct Padded {
        u8 p;
        // Padding of 3 bytes
        u32 a;
    };
    struct Padded2 {
        u32 p;
        u16 a;
        // Padding of 2 bytes
    };
    struct  Derived : A {};
    struct  Derived2 : A {
        virtual void fn() {}
    };
    struct D {
        bool operator==(const D&) { return true; }
    };


    struct F {
        i32 a;
        short b;
        bool operator==(const F&) { return true; }
    };

    struct Comp_E {
        i32 a;
        bool operator==(const Comp_E&) { return true; }
    };

    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};
}

TEST(Traits, IsBitwiseComparable) {
    // i8
    ASSERT_TRUE((hud::IsBitwiseComparableV<i8, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, i64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i8, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, u64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i8, uptr>));

    // u8
    ASSERT_TRUE((hud::IsBitwiseComparableV<u8, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, i64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u8, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, u64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u8, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u8, uptr>));

    // i16
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, i8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i16, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, u8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i16, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<i16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseComparableV<i16, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i16, uptr>));

    // u16
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, i8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u16, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, u8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u16, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<u16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseComparableV<u16, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u16, uptr>));

    // i32
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, i16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, u16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, char16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i32, uptr>));
#endif

    // u32
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, i16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, u16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, char16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u32, uptr>));
#endif

    // i64
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, i32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i64, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, u32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i64, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<i64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseComparableV<i64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<i64, uptr>));
#endif

    // u64
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, i32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u64, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, u32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u64, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<u64, uptr>));
#else
    ASSERT_TRUE((hud::IsBitwiseComparableV<u64, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<u64, uptr>));
#endif

    // ansichar
    ASSERT_TRUE((hud::IsBitwiseComparableV<ansichar, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, i64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<ansichar, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, u64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<ansichar, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<ansichar, uptr>));

    // wchar
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, i8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, i32>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, i16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, i32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, u8>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, u32>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, u16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, u32>));
#endif    
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, wchar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, char16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<wchar, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<wchar, uptr>));

    // char16
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, i8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char16, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, u8>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char16, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_TRUE((hud::IsBitwiseComparableV<char16, wchar>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, wchar>));
#endif
    ASSERT_TRUE((hud::IsBitwiseComparableV<char16, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char16, uptr>));

    // char32
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, i16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, u16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, ansichar>));
#if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, wchar>));
#else
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, wchar>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, char16>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, f64>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<char32, uptr>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<char32, uptr>));
#endif
    // f32
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f32, uptr>));

    // f64
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, i16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, i64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, u16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, u64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, char16>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, char32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, f64>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, iptr>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<f64, uptr>));

    // iptr
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<iptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<iptr, uptr>));

    // uptr
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, i8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, i16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, i32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, i64>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, i32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, i64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, u8>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, u16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, u32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, u64>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, u32>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, u64>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, ansichar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, wchar>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, char16>));
#if defined(HD_TARGET_32_BITS)
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, char32>));
#else
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, char32>));
#endif
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, f32>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<uptr, f64>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, iptr>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<uptr, uptr>));

    

    ASSERT_FALSE((hud::IsBitwiseComparableV<Empty, Empty>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<A, A>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<B, B>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<C, C>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Padded, Padded>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Padded2, Padded2>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Derived, Derived>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Derived2, Derived2>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<D, D>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_E, Comp_E>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<F, F>));

    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_Enum, Comp_Enum>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_Enum2, Comp_Enum2>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_Enum3, Comp_Enum3>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_Enum4, Comp_Enum4>));
    ASSERT_TRUE((hud::IsBitwiseComparableV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Comp_Enum, Comp_Enum4>));
    ASSERT_FALSE((hud::IsBitwiseComparableV<Comp_Enum3, Comp_Enum4>));
}