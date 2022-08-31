#include <OSLayer/Traits/IsComparableWithLessEqual.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A {};
    struct B { bool operator<=(const B&) const noexcept; };
    struct C { bool operator<=(const A&) const noexcept; };
}

TEST(Traits, IsComparableWithLessEqual) {

    // i8
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i8, char32>));

    // u8
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u8, char32>));

    // i16
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i16, char32>));

    // u16
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u16, char32>));

    // i32
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i32, char32>));

    // u32
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u32, char32>));

    // i64
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<i64, char32>));

    // u64
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<u64, char32>));

    // iptr
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<iptr, char32>));

    // uptr
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<uptr, char32>));

    // f32
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f32, char32>));

    // f64
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<f64, char32>));

    // ansichar
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<ansichar, char32>));

    // wchar
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<wchar, char32>));

    // char16
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char16, char32>));

    // char32
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<char32, char32>));

    // enum
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<Comp_Enum, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum, Comp_Enum4>));

    // enum class
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum2, Comp_Enum>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<Comp_Enum2, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum2, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum2, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum3, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum3, Comp_Enum2>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<Comp_Enum3, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum3, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum4, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum4, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<Comp_Enum4, Comp_Enum3>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<Comp_Enum4, Comp_Enum4>));

    ASSERT_FALSE((hud::IsComparableWithLessEqualV<A, A>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<A, B>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<A, C>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<B, A>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<B, B>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<B, C>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<C, A>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<C, B>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<C, C>));

    //pointers
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, A>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, B>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, C>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, void>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, i8>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, i16>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, i32>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, i64>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, iptr>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, u8>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, u16>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, u32>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, u64>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, uptr>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, f32>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, f64>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, ansichar>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, wchar>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, char16>));
    ASSERT_FALSE((hud::IsComparableWithLessEqualV<void*, char32>));

    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, A*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, B*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, C*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, void*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, i8*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, i16*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, i32*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, i64*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, iptr*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, u8*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, u16*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, u32*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, u64*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, uptr*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, f32*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, f64*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, ansichar*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, wchar*>));
    ASSERT_TRUE((hud::IsComparableWithLessEqualV<void*, char16*>));

}