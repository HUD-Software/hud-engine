#include <OSLayer/Containers/SharedPointer.h>
#include <Misc/NonBitwiseType.h>

TEST(SharedPointer_array_safe, default_constructor) {
    using namespace hud;

    const auto test = []()
    {
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr;
        return std::tuple{
            shared_ptr.pointer() == nullptr,
            shared_ptr.shared_count()
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
    }
}

TEST(SharedPointer_array_safe, param_constructor_nullptr) {
    using namespace hud;

    const auto test = []()
    {
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(nullptr);
        return std::tuple{
            shared_ptr.pointer() == nullptr,
            shared_ptr.shared_count()
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_EQ(std::get<1>(result), 0u);
    }
}

TEST(SharedPointer_array_safe, param_constructor_same_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(type);
        return std::tuple{
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 1u,
            shared_ptr.pointer()[0].id() == 1,
            shared_ptr.pointer()[1].id() == 2,
            dtor_count[0] == 0,
            dtor_count[1] == 0
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

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//    }
//#endif
}

TEST(SharedPointer_array_safe, param_constructor_different_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        SharedPointer<const HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(type);
        return std::tuple{
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 1u,
            shared_ptr.pointer()[0].id() == 1,
            shared_ptr.pointer()[1].id() == 2,
            dtor_count[0] == 0,
            dtor_count[1] == 0
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

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//    }
//#endif
}

TEST(SharedPointer_array_safe, copy_constructor_same_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        const SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr_to_copy(type);
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(shared_ptr_to_copy);

        return std::tuple{
            shared_ptr_to_copy.pointer() == type,
            shared_ptr_to_copy.shared_count() == 2u,
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 2u,
            shared_ptr_to_copy.pointer()[0].id() == 1,
            shared_ptr_to_copy.pointer()[0].constructor_count() == 1u,
            shared_ptr_to_copy.pointer()[0].copy_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[0].move_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[0].copy_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[0].move_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[1].id() == 2,
            shared_ptr_to_copy.pointer()[1].constructor_count() == 1u,
            shared_ptr_to_copy.pointer()[1].copy_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[1].move_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[1].copy_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[1].move_constructor_count() == 0u,
            dtor_count[0] == 0,
            dtor_count[1] == 0,
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
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
        ASSERT_TRUE(std::get<16>(result));
        ASSERT_TRUE(std::get<17>(result));
    }

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_TRUE(std::get<10>(result));
//        ASSERT_TRUE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//        ASSERT_TRUE(std::get<15>(result));
//        ASSERT_TRUE(std::get<16>(result));
//        ASSERT_TRUE(std::get<17>(result));
//    }
//#endif
}

TEST(SharedPointer_array_safe, copy_constructor_different_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        const SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr_to_copy(type);
        SharedPointer<const HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(shared_ptr_to_copy);

        return std::tuple{
            shared_ptr_to_copy.pointer() == type,
            shared_ptr_to_copy.shared_count() == 2u,
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 2u,
            shared_ptr_to_copy.pointer()[0].id() == 1,
            shared_ptr_to_copy.pointer()[0].constructor_count() == 1u,
            shared_ptr_to_copy.pointer()[0].copy_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[0].move_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[0].copy_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[0].move_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[1].id() == 2,
            shared_ptr_to_copy.pointer()[1].constructor_count() == 1u,
            shared_ptr_to_copy.pointer()[1].copy_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[1].move_assign_count() == 0u,
            shared_ptr_to_copy.pointer()[1].copy_constructor_count() == 0u,
            shared_ptr_to_copy.pointer()[1].move_constructor_count() == 0u,
            dtor_count[0] == 0,
            dtor_count[1] == 0,
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
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
        ASSERT_TRUE(std::get<16>(result));
        ASSERT_TRUE(std::get<17>(result));
    }

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_TRUE(std::get<10>(result));
//        ASSERT_TRUE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//        ASSERT_TRUE(std::get<15>(result));
//        ASSERT_TRUE(std::get<16>(result));
//        ASSERT_TRUE(std::get<17>(result));
//    }
//#endif
}

TEST(SharedPointer_array_safe, move_constructor_same_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr_to_move(type);
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(move(shared_ptr_to_move));

        return std::tuple{
            shared_ptr_to_move.pointer() == nullptr,
            shared_ptr_to_move.shared_count() == 0u,
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 1u,
            shared_ptr.pointer()[0].id() == 1,
            shared_ptr.pointer()[0].constructor_count() == 1u,
            shared_ptr.pointer()[0].copy_assign_count() == 0u,
            shared_ptr.pointer()[0].move_assign_count() == 0u,
            shared_ptr.pointer()[0].copy_constructor_count() == 0u,
            shared_ptr.pointer()[0].move_constructor_count() == 0u,
            shared_ptr.pointer()[1].id() == 2,
            shared_ptr.pointer()[1].constructor_count() == 1u,
            shared_ptr.pointer()[1].copy_assign_count() == 0u,
            shared_ptr.pointer()[1].move_assign_count() == 0u,
            shared_ptr.pointer()[1].copy_constructor_count() == 0u,
            shared_ptr.pointer()[1].move_constructor_count() == 0u,
            dtor_count[0] == 0,
            dtor_count[1] == 0,
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
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
        ASSERT_TRUE(std::get<16>(result));
        ASSERT_TRUE(std::get<17>(result));
    }

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_TRUE(std::get<10>(result));
//        ASSERT_TRUE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//        ASSERT_TRUE(std::get<15>(result));
//        ASSERT_TRUE(std::get<16>(result));
//        ASSERT_TRUE(std::get<17>(result));
//    }
//#endif
}

TEST(SharedPointer_array_safe, move_constructor_different_type) {
    using namespace hud;

    const auto test = []() {
        i32 dtor_count[2] = { 0,0 };
        HUD_TEST::NonBitwiseType* type = new HUD_TEST::NonBitwiseType[2]{ {1, &dtor_count[0]},{2, &dtor_count[1]} };
        SharedPointer<HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr_to_move(type);
        SharedPointer<const HUD_TEST::NonBitwiseType[2], EThreadSafety::safe> shared_ptr(move(shared_ptr_to_move));

        return std::tuple{
            shared_ptr_to_move.pointer() == nullptr,
            shared_ptr_to_move.shared_count() == 0u,
            shared_ptr.pointer() == type,
            shared_ptr.shared_count() == 1u,
            shared_ptr.pointer()[0].id() == 1,
            shared_ptr.pointer()[0].constructor_count() == 1u,
            shared_ptr.pointer()[0].copy_assign_count() == 0u,
            shared_ptr.pointer()[0].move_assign_count() == 0u,
            shared_ptr.pointer()[0].copy_constructor_count() == 0u,
            shared_ptr.pointer()[0].move_constructor_count() == 0u,
            shared_ptr.pointer()[1].id() == 2,
            shared_ptr.pointer()[1].constructor_count() == 1u,
            shared_ptr.pointer()[1].copy_assign_count() == 0u,
            shared_ptr.pointer()[1].move_assign_count() == 0u,
            shared_ptr.pointer()[1].copy_constructor_count() == 0u,
            shared_ptr.pointer()[1].move_constructor_count() == 0u,
            dtor_count[0] == 0,
            dtor_count[1] == 0,
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
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
        ASSERT_TRUE(std::get<15>(result));
        ASSERT_TRUE(std::get<16>(result));
        ASSERT_TRUE(std::get<17>(result));
    }

    // Constant is not available with thread safe SharedPointer
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_TRUE(std::get<10>(result));
//        ASSERT_TRUE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//        ASSERT_TRUE(std::get<15>(result));
//        ASSERT_TRUE(std::get<16>(result));
//        ASSERT_TRUE(std::get<17>(result));
//    }
//#endif
}