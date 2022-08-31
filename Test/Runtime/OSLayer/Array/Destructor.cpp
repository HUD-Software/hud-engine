#include <OSLayer/Containers/Array.h>
#include "Allocators.h"
#include <OSLayer/Templates/BitCast.h>

TEST(Array, destructor_call_elements_destructors)
{
    using namespace hud;

    // no extra
    {
        auto test_destructor = []() {
            i32 dtor_order[2];
            Memory::set_zero(dtor_order);
            i32* dtor_order_ptr[2] = { &dtor_order[0], &dtor_order[1] };

            bool all_destructor_are_not_called = true;
            {
                Array<HUD_TEST::SetBoolToTrueWhenDestroyed, HUD_TEST::ArrayAllocator<alignof(HUD_TEST::SetBoolToTrueWhenDestroyed)>> array(dtor_order_ptr, 2);
                // Ensure element's destructors are not called
                for (usize index = 0; index < 2; index++) {
                    if (*array[index].ptr() != 0) {
                        all_destructor_are_not_called = false;
                        break;
                    }
                }
            }

            // Ensure element's destructors are called
            bool all_destructor_are_called = true;
            for (usize index = 0; index < 2; index++) {
                if (dtor_order[index] == 0) {
                    all_destructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                all_destructor_are_not_called,
                all_destructor_are_called
            };
        };

        // Non constant
        {
            const auto result = test_destructor();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
        }

        // Constant
        {
            constexpr auto result = test_destructor();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
        }

    }

    // With extra
    {
        auto test_destructor = []() {
            i32 dtor_order[2];
            Memory::set_zero(dtor_order);
            i32* dtor_order_ptr[2] = { &dtor_order[0], &dtor_order[1] };

            bool all_destructor_are_not_called = true;
            {
                Array<HUD_TEST::SetBoolToTrueWhenDestroyed, HUD_TEST::ArrayAllocator<alignof(HUD_TEST::SetBoolToTrueWhenDestroyed)>> array(dtor_order_ptr, 2, 4);
                // Ensure element's destructors are not called
                for (usize index = 0; index < 2; index++) {
                    if (*array[index].ptr() != 0) {
                        all_destructor_are_not_called = false;
                        break;
                    }
                }
            }

            // Ensure element's destructors are called
            bool all_destructor_are_called = true;
            for (usize index = 0; index < 2; index++) {
                if (dtor_order[index] == 0) {
                    all_destructor_are_called = false;
                    break;
                }
            }

            return std::tuple{
                all_destructor_are_not_called,
                all_destructor_are_called
            };
        };

        // Non constant
        {
            const auto result = test_destructor();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
        }

        // Constant
        {
            constexpr auto result = test_destructor();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
        }

    }
}

