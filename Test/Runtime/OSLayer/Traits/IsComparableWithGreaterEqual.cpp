#include <OSLayer/Traits/IsComparableWithGreaterEqual.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A {};
    struct B { bool operator>=(const B&) const noexcept; };
    struct C { bool operator>=(const A&) const noexcept; };
}

TEST(Traits, IsComparableWithGreaterEqual) {

    // i8
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i8, char32>));

    // u8
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u8, char32>));

    // i16
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i16, char32>));

    // u16
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u16, char32>));

    // i32
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i32, char32>));

    // u32
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u32, char32>));

    // i64
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<i64, char32>));

    // u64
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<u64, char32>));

    // iptr
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<iptr, char32>));

    // uptr
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<uptr, char32>));

    // f32
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f32, char32>));

    // f64
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<f64, char32>));

    // ansichar
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<ansichar, char32>));

    // wchar
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<wchar, char32>));

    // char16
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char16, char32>));

    // char32
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<char32, char32>));

    // enum
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<Comp_Enum, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum, Comp_Enum4>));

    // enum class
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum2, Comp_Enum>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<Comp_Enum2, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum2, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum2, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum3, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum3, Comp_Enum2>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<Comp_Enum3, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum3, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum4, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum4, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<Comp_Enum4, Comp_Enum3>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<Comp_Enum4, Comp_Enum4>));


    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<A, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<A, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<A, C>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<B, A>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<B, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<B, C>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<C, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<C, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<C, C>));

    //pointers
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, C>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, void>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, i8>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, i16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, i32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, i64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, iptr>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, u8>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, u16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, u32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, u64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, uptr>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, f32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, f64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, ansichar>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, wchar>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, char16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterEqualV<void*, char32>));

    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, A*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, B*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, C*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, void*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, i8*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, i16*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, i32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, i64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, iptr*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, u8*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, u16*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, u32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, u64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, uptr*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, f32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, f64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, ansichar*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, wchar*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterEqualV<void*, char16*>));
}