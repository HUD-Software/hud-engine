#include <OSLayer/Traits/UnderlyingType.h>

namespace {
    enum e1 {};
    enum class e2 : i8;
    enum class e3 : i16;
    enum class e4 : i32;
    enum class e5 : i64;
    enum class e6 : u8;
    enum class e7 : u16;
    enum class e8 : u32;
    enum class e9 : u64;
    enum class e10 : ansichar;
    enum class e11 : wchar;
    enum class e12 : char16;
    enum class e13 : char32;
    enum class e14 : iptr;
    enum class e15 : uptr;
    enum class e16 : isize;
    enum class e17 : usize;

    enum class e2c : const i8;
    enum class e3c : const i16;
    enum class e4c : const i32;
    enum class e5c : const i64;
    enum class e6c : const u8;
    enum class e7c : const u16;
    enum class e8c : const u32;
    enum class e9c : const u64;
    enum class e10c : const ansichar;
    enum class e11c : const wchar;
    enum class e12c : const char16;
    enum class e13c : const char32;
    enum class e14c : const iptr;
    enum class e15c : const uptr;
    enum class e16c : const isize;
    enum class e17c : const usize;

    enum class e2v : volatile i8;
    enum class e3v : volatile i16;
    enum class e4v : volatile i32;
    enum class e5v : volatile i64;
    enum class e6v : volatile u8;
    enum class e7v : volatile u16;
    enum class e8v : volatile u32;
    enum class e9v : volatile u64;
    enum class e10v : volatile ansichar;
    enum class e11v : volatile wchar;
    enum class e12v : volatile char16;
    enum class e13v : volatile char32;
    enum class e14v : volatile iptr;
    enum class e15v : volatile uptr;
    enum class e16v : volatile isize;
    enum class e17v : volatile usize;

    enum class e2cv : const volatile i8;
    enum class e3cv : const volatile i16;
    enum class e4cv : const volatile i32;
    enum class e5cv : const volatile i64;
    enum class e6cv : const volatile u8;
    enum class e7cv : const volatile u16;
    enum class e8cv : const volatile u32;
    enum class e9cv : const volatile u64;
    enum class e10cv : const volatile ansichar;
    enum class e11cv : const volatile wchar;
    enum class e12cv : const volatile char16;
    enum class e13cv : const volatile char32;
    enum class e14cv : const volatile iptr;
    enum class e15cv : const volatile uptr;
    enum class e16cv : const volatile isize;
    enum class e17cv : const volatile usize;
}

TEST(Traits, UnderlyingType) {
    // MSVC and ClangCL promote the enum an signed int when GCC and Clang promote it to unsigned int
    #if defined(HD_COMPILER_MSVC) || defined(HD_COMPILER_CLANG_CL)
        ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e1>, i32>));
    #else 
        ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e1>, u32>));
    #endif
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e2>, i8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e3>, i16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e4>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e5>, i64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e6>, u8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e7>, u16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e8>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e9>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e10>, ansichar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e11>, wchar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e12>, char16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e13>, char32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e14>, iptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e15>, uptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e16>, isize>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e17>, usize>));

    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e2c>, i8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e3c>, i16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e4c>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e5c>, i64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e6c>, u8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e7c>, u16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e8c>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e9c>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e10c>, ansichar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e11c>, wchar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e12c>, char16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e13c>, char32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e14c>, iptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e15c>, uptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e16c>, isize>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e17c>, usize>));

    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e2v>, i8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e3v>, i16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e4v>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e5v>, i64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e6v>, u8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e7v>, u16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e8v>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e9v>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e10v>, ansichar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e11v>, wchar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e12v>, char16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e13v>, char32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e14v>, iptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e15v>, uptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e16v>, isize>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e17v>, usize>));

    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e2cv>, i8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e3cv>, i16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e4cv>, i32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e5cv>, i64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e6cv>, u8>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e7cv>, u16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e8cv>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e9cv>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e10cv>, ansichar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e11cv>, wchar>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e12cv>, char16>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e13cv>, char32>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e14cv>, iptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e15cv>, uptr>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e16cv>, isize>));
    ASSERT_TRUE((hud::IsSameV<hud::UnderlyingTypeT<e17cv>, usize>));
}