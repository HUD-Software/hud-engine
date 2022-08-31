#include <OSLayer/Traits/Decay.h>

TEST(Traits, Decay) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<DecayT<i32>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32&>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32&&>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<const i32&>, i32>));
    ASSERT_FALSE((IsSameV<DecayT<i32[]>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32[]>, i32*>));
    ASSERT_FALSE((IsSameV<DecayT<i32[2]>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32[2]>, i32*>));
    ASSERT_FALSE((IsSameV<DecayT<i32*>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32*>, i32*>));
    ASSERT_FALSE((IsSameV<DecayT<i32(i32)>, i32>));
    ASSERT_TRUE((IsSameV<DecayT<i32(i32)>, i32(*)(i32)>));
}

