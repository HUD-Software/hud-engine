#include <OSLayer/Containers/SharedPointer.h>
#include <Misc/NonBitwiseType.h>

TEST(SharedPointer__safe, destructor) {

    const auto test = []() {
        i32 dtor_count = 0;
        {
            hud::SharedPointer<HUD_TEST::NonBitwiseType, hud::EThreadSafety::safe> ptr(new HUD_TEST::NonBitwiseType(123, &dtor_count));
            {
                hud::SharedPointer<HUD_TEST::NonBitwiseType, hud::EThreadSafety::safe> ptr_2(ptr);
            } // dtor_count == 0

        } // dtor_count == 1
        return dtor_count;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(result);
    }

    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(result);
    }
}