#include <OSLayer/Containers/SharedPointer.h>
#include <Misc/NonBitwiseType.h>

TEST(SharedPointer_not_safe, swap_with_empty) {
    using namespace hud;

    // SharedPointer::swap
    {
        const auto test = []() {
            i32 dtor_count = 0;
            auto ptr = new HUD_TEST::NonBitwiseType(1, &dtor_count);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr(ptr);
            const bool is_pointer_correct = shared_ptr.pointer();
            const u32 shared_count_before = shared_ptr.shared_count();

            SharedPointer<HUD_TEST::NonBitwiseType> empty;
            shared_ptr.swap(empty);

            return std::tuple{
                dtor_count == 0,
                is_pointer_correct,
                shared_count_before == 1u,
                shared_ptr.pointer() == nullptr,
                shared_ptr.shared_count() == 0u 
            };
        };


        // Non constant
        {
            const auto result = test();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
            ASSERT_TRUE(std::get<2>(result));
            ASSERT_TRUE(std::get<3>(result));
            ASSERT_TRUE(std::get<4>(result));
        }

        // Constant
        // Not working under with msvc
        // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//        {
//            constexpr auto result = test();
//            ASSERT_TRUE(std::get<0>(result));
//            ASSERT_TRUE(std::get<1>(result));
//            ASSERT_TRUE(std::get<2>(result));
//            ASSERT_TRUE(std::get<3>(result));
//            ASSERT_TRUE(std::get<4>(result));
//        }
//#endif
    }

    // hud::swap
    {
        const auto test = []() {
            i32 dtor_count = 0;
            auto ptr = new HUD_TEST::NonBitwiseType(1, &dtor_count);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr(ptr);
            const bool is_pointer_correct = shared_ptr.pointer();
            const u32 shared_count_before = shared_ptr.shared_count();

            SharedPointer<HUD_TEST::NonBitwiseType> empty;
            swap(shared_ptr, empty);

            return std::tuple{
                dtor_count == 0,
                is_pointer_correct,
                shared_count_before == 1u,
                shared_ptr.pointer() == nullptr,
                shared_ptr.shared_count() == 0u
            };
        };


        // Non constant
        {
            const auto result = test();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
            ASSERT_TRUE(std::get<2>(result));
            ASSERT_TRUE(std::get<3>(result));
            ASSERT_TRUE(std::get<4>(result));
        }

        // Constant
        // Not working under with msvc
        // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//        {
//            constexpr auto result = test();
//            ASSERT_TRUE(std::get<0>(result));
//            ASSERT_TRUE(std::get<1>(result));
//            ASSERT_TRUE(std::get<2>(result));
//            ASSERT_TRUE(std::get<3>(result));
//            ASSERT_TRUE(std::get<4>(result));
//        }
//#endif
    }
}

TEST(SharedPointer_not_safe, swap_same_type) {
    using namespace hud;

    // SharedPointer::swap
    {
        const auto test = []() {
            i32 dtor_count = 0;
            i32 dtor_count_1 = 0;

            auto ptr = new HUD_TEST::NonBitwiseType(1, &dtor_count);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr(ptr);

            auto ptr2 = new HUD_TEST::NonBitwiseType(2, &dtor_count_1);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr_2(ptr2);
            shared_ptr.swap(shared_ptr_2);

            return std::tuple{
                dtor_count == 0,
                dtor_count_1 == 0,
                shared_ptr.pointer() == ptr2,
                shared_ptr.shared_count() == 1u,
                shared_ptr_2.pointer() == ptr,
                shared_ptr_2.shared_count() == 1u
            };
        };


        // Non constant
        {
            const auto result = test();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
            ASSERT_TRUE(std::get<2>(result));
            ASSERT_TRUE(std::get<3>(result));
            ASSERT_TRUE(std::get<4>(result));
            ASSERT_TRUE(std::get<5>(result));
        }

        // Constant
        // Not working under with msvc
        // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//        {
//            constexpr auto result = test();
//            ASSERT_TRUE(std::get<0>(result));
//            ASSERT_TRUE(std::get<1>(result));
//            ASSERT_TRUE(std::get<2>(result));
//            ASSERT_TRUE(std::get<3>(result));
//            ASSERT_TRUE(std::get<4>(result));
//            ASSERT_TRUE(std::get<5>(result));
//        }
//#endif
    }

    // hud::swap
    {
        const auto test = []() {
            i32 dtor_count = 0;
            i32 dtor_count_1 = 0;

            auto ptr = new HUD_TEST::NonBitwiseType(1, &dtor_count);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr(ptr);

            auto ptr2 = new HUD_TEST::NonBitwiseType(2, &dtor_count_1);
            SharedPointer<HUD_TEST::NonBitwiseType> shared_ptr_2(ptr2);
            swap(shared_ptr, shared_ptr_2);

            return std::tuple{
                dtor_count == 0,
                dtor_count_1 == 0,
                shared_ptr.pointer() == ptr2,
                shared_ptr.shared_count() == 1u,
                shared_ptr_2.pointer() == ptr,
                shared_ptr_2.shared_count() == 1u
            };
        };


        // Non constant
        {
            const auto result = test();
            ASSERT_TRUE(std::get<0>(result));
            ASSERT_TRUE(std::get<1>(result));
            ASSERT_TRUE(std::get<2>(result));
            ASSERT_TRUE(std::get<3>(result));
            ASSERT_TRUE(std::get<4>(result));
            ASSERT_TRUE(std::get<5>(result));
    }

        // Constant
        // Not working under with msvc
        // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//        {
//            constexpr auto result = test();
//            ASSERT_TRUE(std::get<0>(result));
//            ASSERT_TRUE(std::get<1>(result));
//            ASSERT_TRUE(std::get<2>(result));
//            ASSERT_TRUE(std::get<3>(result));
//            ASSERT_TRUE(std::get<4>(result));
//            ASSERT_TRUE(std::get<5>(result));
//        }
//#endif
    }
}