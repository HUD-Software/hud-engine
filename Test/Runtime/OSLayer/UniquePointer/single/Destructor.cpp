#include <OSLayer/Containers/UniquePointer.h>
#include <Misc/NonBitwiseType.h>

TEST(UniquePointer, destructor) {

    const auto test = []() {
        i32 dtor_count = 0;
        {
            hud::UniquePointer<HUD_TEST::NonBitwiseType> ptr(new HUD_TEST::NonBitwiseType(123, &dtor_count));
        }
        return dtor_count == 1;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(result);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(result);
    }
}

TEST(UniquePointer, destructor_after_move) {

    const auto test = []() {
        i32 dtor_count = 0;
        {
            hud::UniquePointer<HUD_TEST::NonBitwiseType> ptr(new HUD_TEST::NonBitwiseType(123, &dtor_count));
            hud::UniquePointer<HUD_TEST::NonBitwiseType> other(hud::move(ptr));
        }

        return dtor_count == 1;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(result);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(result);
    }
}