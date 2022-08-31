#include <OSLayer/Containers/SharedPointer.h>
#include <Misc/NonBitwiseType.h>
#include <array>

TEST(SharedPointer_array_not_safe, destructor) {

    const auto test = []() {
        i32 dtor_count[4] = { 0 };
        {
            hud::SharedPointer<HUD_TEST::NonBitwiseType[4]> ptr(new HUD_TEST::NonBitwiseType[4]{ { 123, &dtor_count[0] }, { 123, &dtor_count[1] }, { 123, &dtor_count[2] }, { 123, &dtor_count[3] } });
            {
                hud::SharedPointer<HUD_TEST::NonBitwiseType[4]> ptr_2(ptr);
            } // dtor_count == 0

        } // dtor_count == 1
        return std::array{
            dtor_count[0] == 1,
            dtor_count[1] == 1,
            dtor_count[2] == 1,
            dtor_count[3] == 1,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }

    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }
}