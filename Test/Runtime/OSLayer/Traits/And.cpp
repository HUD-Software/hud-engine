#include <OSLayer/Traits/And.h>

TEST(Traits, And) {
    using namespace hud;

    ASSERT_TRUE(AndV<TrueType>);
    ASSERT_FALSE(AndV<FalseType>);
    ASSERT_FALSE((AndV<TrueType, FalseType>));
    ASSERT_FALSE((AndV<FalseType, TrueType>));
    ASSERT_TRUE((AndV<TrueType, TrueType, TrueType>));
    ASSERT_FALSE((AndV<TrueType, TrueType, FalseType>));
    ASSERT_FALSE((AndV<FalseType, FalseType>));
}