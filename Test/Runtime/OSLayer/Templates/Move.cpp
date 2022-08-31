#include <OSLayer/Templates/Move.h>

TEST(Templates, move) {
    using namespace hud;

    i32 a{};
    ASSERT_TRUE(IsRValueReferenceV<decltype(move(a))>);
    ASSERT_FALSE(IsLValueReferenceV<decltype(move(a))>);

    const i32 a_const{};
    ASSERT_TRUE(IsRValueReferenceV<decltype(move(a_const))>);
    ASSERT_FALSE(IsLValueReferenceV<decltype(move(a_const))>);
}