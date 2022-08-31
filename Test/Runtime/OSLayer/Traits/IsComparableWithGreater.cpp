#include <OSLayer/Traits/IsComparableWithGreater.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A {};
    struct B { bool operator>(const B&) const noexcept; };
    struct C { bool operator>(const A&) const noexcept; };
}

TEST(Traits, IsComparableWithGreater) {

    // i8
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i8, char32>));

    // u8
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u8, char32>));

    // i16
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i16, char32>));

    // u16
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u16, char32>));

    // i32
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i32, char32>));

    // u32
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u32, char32>));

    // i64
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<i64, char32>));

    // u64
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<u64, char32>));

    // iptr
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<iptr, char32>));

    // uptr
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<uptr, char32>));

    // f32
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f32, char32>));

    // f64
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<f64, char32>));

    // ansichar
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<ansichar, char32>));

    // wchar
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<wchar, char32>));

    // char16
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char16, char32>));

    // char32
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, i8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, i16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, i32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, i64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, u8>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, u16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, u32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, u64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, f32>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, f64>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, char16>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<char32, char32>));

    // enum
    ASSERT_TRUE((hud::IsComparableWithGreaterV<Comp_Enum, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum, Comp_Enum4>));

    // enum class
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum2, Comp_Enum>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<Comp_Enum2, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum2, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum2, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum3, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum3, Comp_Enum2>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<Comp_Enum3, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum3, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum4, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum4, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<Comp_Enum4, Comp_Enum3>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<Comp_Enum4, Comp_Enum4>));


    ASSERT_FALSE((hud::IsComparableWithGreaterV<A, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<A, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<A, C>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<B, A>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<B, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<B, C>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<C, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<C, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<C, C>));

    //pointers
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, A>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, B>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, C>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, void>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, i8>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, i16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, i32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, i64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, iptr>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, u8>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, u16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, u32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, u64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, uptr>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, f32>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, f64>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, ansichar>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, wchar>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, char16>));
    ASSERT_FALSE((hud::IsComparableWithGreaterV<void*, char32>));

    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, A*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, B*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, C*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, void*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, i8*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, i16*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, i32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, i64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, iptr*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, u8*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, u16*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, u32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, u64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, uptr*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, f32*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, f64*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, ansichar*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, wchar*>));
    ASSERT_TRUE((hud::IsComparableWithGreaterV<void*, char16*>));
}