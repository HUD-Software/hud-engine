#include <OSLayer/Templates/Forward.h>
#include <OSLayer/Traits/IsRValueReference.h>

TEST(Templates, forward) {
    using namespace hud;

    ASSERT_TRUE(IsRValueReferenceV<decltype(forward<i32>(i32{})) > );
    ASSERT_FALSE(IsLValueReferenceV<decltype(forward<i32>(i32{})) > );

    ASSERT_TRUE(IsRValueReferenceV<decltype(forward<const i32>(i32{})) > );
    ASSERT_FALSE(IsLValueReferenceV<decltype(forward<const i32>(i32{})) > );
}