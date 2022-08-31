#include <OSLayer/Traits/HasUniqueObjectRepresentations.h>

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
    struct  Derived : A {};

    struct  Derived2 : A {
        virtual void fn() {}
    };
}

TEST(Traits, HasUniqueObjectRepresentations) {
    using namespace hud;

    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32*>);
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<i32&>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32[]>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32[][2]>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32[2]>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<i32[2][2]>);
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<VoidT<>>);
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<f32>);
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<f64>);

    
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<Empty>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<A>);
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<B>);
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<C>);

    
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<Padded>);

    
    ASSERT_TRUE(HasUniqueObjectRepresentationsV<Derived>);

    
    ASSERT_FALSE(HasUniqueObjectRepresentationsV<Derived2>);
}