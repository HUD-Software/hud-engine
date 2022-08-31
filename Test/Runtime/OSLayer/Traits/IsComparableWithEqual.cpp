#include <OSLayer/Traits/IsComparableWithEqual.h>

namespace {
    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A {};
    struct B { bool operator==(const B&) const noexcept; };
    struct C { bool operator==(const A&) const noexcept { return true; } };
}

TEST(Traits, IsComparableWithEqual) {

    // i8
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i8, char32>));

    // u8
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u8, char32>));

    // i16
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i16, char32>));

    // u16
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u16, char32>));

    // i32
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i32, char32>));

    // u32
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u32, char32>));

    // i64
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<i64, char32>));

    // u64
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<u64, char32>));

    // iptr
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<iptr, char32>));

    // uptr
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<uptr, char32>));

    // f32
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f32, char32>));

    // f64
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<f64, char32>));

    // ansichar
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<ansichar, char32>));

    // wchar
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<wchar, char32>));

    // char16
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char16, char32>));

    // char32
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, i8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, i16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, i32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, i64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, u8>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, u16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, u32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, u64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, f32>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, f64>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, char16>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<char32, char32>));


    // enum
    ASSERT_TRUE((hud::IsComparableWithEqualV<Comp_Enum, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum, Comp_Enum4>));

    // enum class
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum2, Comp_Enum>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<Comp_Enum2, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum2, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum2, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum3, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum3, Comp_Enum2>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<Comp_Enum3, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum3, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum4, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum4, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<Comp_Enum4, Comp_Enum3>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<Comp_Enum4, Comp_Enum4>));

    ASSERT_FALSE((hud::IsComparableWithEqualV<A, A>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<A, B>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<A, C>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<B, A>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<B, B>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<B, C>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<C, A>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<C, B>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<C, C>));

    //pointers
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, A>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, B>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, C>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, void>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, i8>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, i16>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, i32>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, i64>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, iptr>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, u8>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, u16>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, u32>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, u64>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, uptr>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, f32>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, f64>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, ansichar>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, wchar>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, char16>));
    ASSERT_FALSE((hud::IsComparableWithEqualV<void*, char32>));

    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, A*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, B*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, C*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, void*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, i8*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, i16*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, i32*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, i64*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, iptr*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, u8*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, u16*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, u32*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, u64*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, uptr*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, f32*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, f64*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, ansichar*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, wchar*>));
    ASSERT_TRUE((hud::IsComparableWithEqualV<void*, char16*>));
}