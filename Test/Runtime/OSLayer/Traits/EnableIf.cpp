#include <OSLayer/Traits/EnableIf.h>

namespace {
    class A {};

    template <typename T>
    typename hud::EnableIfT<hud::IsIntegralV<T>, bool> EnableIfFctIsIntegral() { 
        return true; 
    }

    template <typename T>
    typename hud::EnableIfT<!hud::IsIntegralV<T>, bool> EnableIfFctIsIntegral() { 
        return false; 
    }
}

TEST(Traits, EnableIf)
{
    ASSERT_TRUE(EnableIfFctIsIntegral<i32>());
    ASSERT_TRUE(EnableIfFctIsIntegral<i8>());
    ASSERT_FALSE(EnableIfFctIsIntegral<A>());
}