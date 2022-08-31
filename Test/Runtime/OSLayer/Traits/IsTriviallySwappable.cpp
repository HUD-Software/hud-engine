#include <OSLayer/Traits/IsTriviallySwappable.h>

namespace {
    struct A {
        void fn_a() {};
        void fn_a2() const {};
        void fn_a3() volatile {};
        void fn_a4() const volatile {};
        int a = 0;
        const int a1 = 0;
        volatile int a2 = 0;
        const volatile int a3 = 0;
    };
    [[maybe_unused]] void(A::* pt)() = &A::fn_a;
    [[maybe_unused]] void(A::* pt2)() const = &A::fn_a2;
    [[maybe_unused]] void(A::* pt3)() volatile = &A::fn_a3;
    [[maybe_unused]] void(A::* pt4)() const volatile = &A::fn_a4;
    enum E {};

    struct Yes { };
    struct NoDtor {
        ~NoDtor() noexcept {}
    };

    struct NoMoveCtor {
        NoMoveCtor(NoMoveCtor&&) noexcept {}

    };

    struct NoMoveAssign {
        NoMoveAssign& operator=(NoMoveAssign&&) noexcept { return *this; }

    };
      
    struct No {
        No(No&&)noexcept {}
        No& operator=(No&&) noexcept { return *this; }
        ~No() noexcept {}
    };
}

TEST(Traits, IsTriviallySwappable) {
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<iptr>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<uptr>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<isize>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<usize>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<ansichar>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<wchar>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<char16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<char32>));

    ASSERT_TRUE((hud::IsTriviallySwappableV<i8*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<iptr*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<uptr*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f32*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f32*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f64*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<f64*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<isize*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<usize*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<ansichar*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<wchar*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<char16*>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<char32*>));

    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)()>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)() const>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)() volatile>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)() const volatile>));

    ASSERT_TRUE((hud::IsTriviallySwappableV<decltype(pt)>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<decltype(pt2)>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<decltype(pt3)>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<decltype(pt4)>));

    
    ASSERT_TRUE((hud::IsTriviallySwappableV<E>));

    ASSERT_TRUE((hud::IsTriviallySwappableV<Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoDtor>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveCtor>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveAssign>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<No>));
   


    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i8, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u8, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i16, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u16, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i32, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u32, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<i64, u64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, i8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, u8>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, i16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, u16>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, i32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, u32>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, i64>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<u64, u64>));


    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)(), void(A::*)()>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)(), void(A::*)() const>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)(), void(A::*)() volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)(), void(A::*)() const volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const, void(A::*)()>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)()const, void(A::*)() const>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const, void(A::*)() volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const, void(A::*)() const volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()volatile, void(A::*)()>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()volatile, void(A::*)() const>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)()volatile, void(A::*)() volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()volatile, void(A::*)() const volatile>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const volatile, void(A::*)()>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const volatile, void(A::*)() const>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<void(A::*)()const volatile, void(A::*)() volatile>));
    ASSERT_TRUE((hud::IsTriviallySwappableV<void(A::*)()const volatile, void(A::*)() const volatile>));



    ASSERT_TRUE((hud::IsTriviallySwappableV<Yes, Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<Yes, No>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<No, Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<No, No>));

    ASSERT_FALSE((hud::IsTriviallySwappableV<NoDtor, NoDtor>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoDtor, Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<Yes, NoDtor>));

    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveCtor, NoMoveCtor>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveCtor, Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<Yes, NoMoveCtor>));

    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveAssign, NoMoveAssign>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<NoMoveAssign, Yes>));
    ASSERT_FALSE((hud::IsTriviallySwappableV<Yes, NoMoveAssign>));
}