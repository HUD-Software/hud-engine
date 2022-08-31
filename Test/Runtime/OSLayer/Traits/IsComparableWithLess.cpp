#include <OSLayer/Traits/IsComparableWithLess.h>

namespace {

    enum Comp_Enum {};
    enum class Comp_Enum2 {};
    enum class Comp_Enum3 : u8 {};
    enum class Comp_Enum4 : u64 {};

    struct A {};
    struct B { bool operator<(const B&) const noexcept; };
    struct C { bool operator<(const A&) const noexcept; };

}

TEST(Traits, IsComparableWithLess) {

    // i8
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i8, char32>));

    // u8
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u8, char32>));

    // i16
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i16, char32>));

    // u16
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u16, char32>));

    // i32
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i32, char32>));

    // u32
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u32, char32>));

    // i64
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<i64, char32>));

    // u64
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<u64, char32>));

    // iptr
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<iptr, char32>));

    // uptr
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<uptr, char32>));

    // f32
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f32, char32>));

    // f64
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<f64, char32>));

    // ansichar
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<ansichar, char32>));

    // wchar
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<wchar, char32>));

    // char16
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char16, char32>));

    // char32
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, i8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, i16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, i32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, i64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, iptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, u8>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, u16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, u32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, u64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, uptr>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, f32>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, f64>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, ansichar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, wchar>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, char16>));
    ASSERT_TRUE((hud::IsComparableWithLessV<char32, char32>));
        
    // enum
    ASSERT_TRUE((hud::IsComparableWithLessV<Comp_Enum, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum, Comp_Enum4>));

    // enum class
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum2, Comp_Enum>));
    ASSERT_TRUE((hud::IsComparableWithLessV<Comp_Enum2, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum2, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum2, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum3, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum3, Comp_Enum2>));
    ASSERT_TRUE((hud::IsComparableWithLessV<Comp_Enum3, Comp_Enum3>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum3, Comp_Enum4>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum4, Comp_Enum>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum4, Comp_Enum2>));
    ASSERT_FALSE((hud::IsComparableWithLessV<Comp_Enum4, Comp_Enum3>));
    ASSERT_TRUE((hud::IsComparableWithLessV<Comp_Enum4, Comp_Enum4>));

    ASSERT_FALSE((hud::IsComparableWithLessV<A, A>));
    ASSERT_FALSE((hud::IsComparableWithLessV<A, B>));
    ASSERT_FALSE((hud::IsComparableWithLessV<A, C>));
    ASSERT_FALSE((hud::IsComparableWithLessV<B, A>));
    ASSERT_TRUE((hud::IsComparableWithLessV<B, B>));
    ASSERT_FALSE((hud::IsComparableWithLessV<B, C>));
    ASSERT_TRUE((hud::IsComparableWithLessV<C, A>));
    ASSERT_FALSE((hud::IsComparableWithLessV<C, B>));
    ASSERT_FALSE((hud::IsComparableWithLessV<C, C>));

    //pointers
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, A>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, B>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, C>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, void>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, i8>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, i16>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, i32>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, i64>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, iptr>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, u8>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, u16>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, u32>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, u64>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, uptr>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, f32>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, f64>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, ansichar>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, wchar>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, char16>));
    ASSERT_FALSE((hud::IsComparableWithLessV<void*, char32>));

    ASSERT_TRUE((hud::IsComparableWithLessV<void*, A*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, B*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, C*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, void*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, i8*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, i16*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, i32*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, i64*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, iptr*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, u8*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, u16*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, u32*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, u64*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, uptr*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, f32*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, f64*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, ansichar*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, wchar*>));
    ASSERT_TRUE((hud::IsComparableWithLessV<void*, char16*>));
}