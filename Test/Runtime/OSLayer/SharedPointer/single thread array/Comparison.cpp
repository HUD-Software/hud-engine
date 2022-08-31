#include <OSLayer/Containers/SharedPointer.h>
#include <Misc/NonBitwiseType.h>

TEST(SharedPointer_array_not_safe, equal_operator) {
    using namespace hud;

    const auto test = []() {
        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p(new i32[2]{ 1,2 });
        SharedPointer<i32[2]> p2(p);
        SharedPointer<i32[2]> p3(new i32[2]{ 3,4 });

        return std::tuple{
            empty == empty,
            empty == p,
            p == p2,
            p2 == p,
            p == p3,
            p3 == p,
            empty == nullptr,
            p == nullptr,
            nullptr == empty,
            nullptr == p,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_FALSE(std::get<4>(result));
        ASSERT_FALSE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_FALSE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_FALSE(std::get<9>(result));
    }

    // Constant
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_FALSE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_FALSE(std::get<4>(result));
//        ASSERT_FALSE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_FALSE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_FALSE(std::get<9>(result));
//    }
//#endif
}

TEST(SharedPointer_array_not_safe, not_equal_operator) {
    using namespace hud;

    const auto test = []() {
        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p(new i32[2]{ 1,2 });
        SharedPointer<i32[2]> p2(p);
        SharedPointer<i32[2]> p3(new i32[2]{ 3,4 });

        return std::tuple{
            empty != empty,
            empty != p,
            p != p2,
            p2 != p,
            p != p3,
            p3 != p,
            empty != nullptr,
            p != nullptr,
            nullptr != empty,
            nullptr != p,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_FALSE(std::get<2>(result));
        ASSERT_FALSE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_FALSE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_FALSE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
    }

    // Constant
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_FALSE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_FALSE(std::get<2>(result));
//        ASSERT_FALSE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_FALSE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_FALSE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//    }
//#endif
}

TEST(SharedPointer_array_not_safe, less_operator) {
    using namespace hud;

    const auto test = []() {
        i32* ptri_1 = new i32[2];
        i32* ptri_2 = new i32[2];
        i32* buf[2];

        // Sort pointer in order
        if (ptri_1 < ptri_2) {
            buf[0] = ptri_1;
            buf[1] = ptri_2;
        }
        else {
            buf[0] = ptri_2;
            buf[1] = ptri_1;
        }
        i32* ptr1 = buf[0];
        i32* ptr2 = buf[1];

        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p1(ptr1);
        SharedPointer<i32[2]> p2(ptr2);

        return std::tuple{
            empty < empty,
            empty < p1,
            empty < p2,
            p1 < empty,
            p1 < p1,
            p1 < p2,
            p2 < empty,
            p2 < p1,
            p2 < p2,
            empty < nullptr,
            p1 < nullptr,
            p2 < nullptr,
            nullptr < empty,
            nullptr < p1,
            nullptr < p2,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_FALSE(std::get<3>(result));
        ASSERT_FALSE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_FALSE(std::get<6>(result));
        ASSERT_FALSE(std::get<7>(result));
        ASSERT_FALSE(std::get<8>(result));
        ASSERT_FALSE(std::get<9>(result));
        ASSERT_FALSE(std::get<10>(result));
        ASSERT_FALSE(std::get<11>(result));
        ASSERT_FALSE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
    }

    // Constant
    // Not testable due to lack of pointer sort at compile time
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_FALSE(std::get<0>(result));
//        ASSERT_FALSE(std::get<1>(result));
//        ASSERT_FALSE(std::get<2>(result));
//        ASSERT_FALSE(std::get<3>(result));
//        ASSERT_FALSE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_FALSE(std::get<6>(result));
//        ASSERT_FALSE(std::get<7>(result));
//        ASSERT_FALSE(std::get<8>(result));
//        ASSERT_FALSE(std::get<9>(result));
//        ASSERT_FALSE(std::get<10>(result));
//        ASSERT_FALSE(std::get<11>(result));
//        ASSERT_FALSE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//    }
//#endif
}


TEST(SharedPointer_array_not_safe, less_equal_operator) {
    using namespace hud;

    const auto test = []() {
        i32* ptri_1 = new i32[2];
        i32* ptri_2 = new i32[2];
        i32* buf[2];

        // Sort pointer in order
        if (Less<i32*>()(ptri_1, ptri_2)) {
            buf[0] = ptri_1;
            buf[1] = ptri_2;
        }
        else {
            buf[0] = ptri_2;
            buf[1] = ptri_1;
        }
        i32* ptr1 = buf[0];
        i32* ptr2 = buf[1];

        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p1(ptr1);
        SharedPointer<i32[2]> p2(ptr2);

        return std::tuple{
            empty <= empty,
            empty <= p1,
            empty <= p2,
            p1 <= empty,
            p1 <= p1,
            p1 <= p2,
            p2 <= empty,
            p2 <= p1,
            p2 <= p2,
            empty <= nullptr,
            p1 <= nullptr,
            p2 <= nullptr,
            nullptr <= empty,
            nullptr <= p1,
            nullptr <= p2,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_FALSE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_FALSE(std::get<6>(result));
        ASSERT_FALSE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_FALSE(std::get<10>(result));
        ASSERT_FALSE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
        ASSERT_TRUE(std::get<14>(result));
    }

    // Constant
    // Not testable due to lack of pointer sort at compile time
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_TRUE(std::get<1>(result));
//        ASSERT_TRUE(std::get<2>(result));
//        ASSERT_FALSE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_TRUE(std::get<5>(result));
//        ASSERT_FALSE(std::get<6>(result));
//        ASSERT_FALSE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_FALSE(std::get<10>(result));
//        ASSERT_FALSE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_TRUE(std::get<13>(result));
//        ASSERT_TRUE(std::get<14>(result));
//    }
//#endif
}

TEST(SharedPointer_array_not_safe, greater_operator) {
    using namespace hud;

    const auto test = []() {
        i32* ptri_1 = new i32[2];
        i32* ptri_2 = new i32[2];
        i32* buf[2];

        // Sort pointer in order
        if (ptri_1 < ptri_2) {
            buf[0] = ptri_1;
            buf[1] = ptri_2;
        }
        else {
            buf[0] = ptri_2;
            buf[1] = ptri_1;
        }
        i32* ptr1 = buf[0];
        i32* ptr2 = buf[1];

        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p1(ptr1);
        SharedPointer<i32[2]> p2(ptr2);

        return std::tuple{
            empty > empty,
            empty > p1,
            empty > p2,
            p1 > empty,
            p1 > p1,
            p1 > p2,
            p2 > empty,
            p2 > p1,
            p2 > p2,
            empty > nullptr,
            p1 > nullptr,
            p2 > nullptr,
            nullptr > empty,
            nullptr > p1,
            nullptr > p2,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_FALSE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
        ASSERT_FALSE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_FALSE(std::get<4>(result));
        ASSERT_FALSE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_FALSE(std::get<8>(result));
        ASSERT_FALSE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_FALSE(std::get<12>(result));
        ASSERT_FALSE(std::get<13>(result));
        ASSERT_FALSE(std::get<14>(result));
    }

    // Constant
    // Not testable due to lack of pointer sort at compile time
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//     ASSERT_FALSE(std::get<0>(result));
//     ASSERT_FALSE(std::get<1>(result));
//     ASSERT_FALSE(std::get<2>(result));
//     ASSERT_TRUE(std::get<3>(result));
//     ASSERT_FALSE(std::get<4>(result));
//     ASSERT_FALSE(std::get<5>(result));
//     ASSERT_TRUE(std::get<6>(result));
//     ASSERT_TRUE(std::get<7>(result));
//     ASSERT_FALSE(std::get<8>(result));
//     ASSERT_FALSE(std::get<9>(result));
//     ASSERT_TRUE(std::get<10>(result));
//     ASSERT_TRUE(std::get<11>(result));
//     ASSERT_FALSE(std::get<12>(result));
//     ASSERT_FALSE(std::get<13>(result));
//     ASSERT_FALSE(std::get<14>(result));
//    }
//#endif
}

TEST(SharedPointer_array_not_safe, greater_equal_operator) {
    using namespace hud;

    const auto test = []() {
        i32* ptri_1 = new i32[2];
        i32* ptri_2 = new i32[2];
        i32* buf[2];

        // Sort pointer in order
        if (ptri_1 < ptri_2) {
            buf[0] = ptri_1;
            buf[1] = ptri_2;
        }
        else {
            buf[0] = ptri_2;
            buf[1] = ptri_1;
        }
        i32* ptr1 = buf[0];
        i32* ptr2 = buf[1];

        SharedPointer<i32[2]> empty;
        SharedPointer<i32[2]> p1(ptr1);
        SharedPointer<i32[2]> p2(ptr2);

        return std::tuple{
            empty >= empty,
            empty >= p1,
            empty >= p2,
            p1 >= empty,
            p1 >= p1,
            p1 >= p2,
            p2 >= empty,
            p2 >= p1,
            p2 >= p2,
            empty >= nullptr,
            p1 >= nullptr,
            p2 >= nullptr,
            nullptr >= empty,
            nullptr >= p1,
            nullptr >= p2,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
        ASSERT_FALSE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_FALSE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_FALSE(std::get<13>(result));
        ASSERT_FALSE(std::get<14>(result));
    }

    // Constant
    // Not testable due to lack of pointer sort at compile time
    // Not working under with msvc
    // https://developercommunity.visualstudio.com/t/constant-evaluation-with-do-not-works-wi/10058244
//#if !defined(HD_COMPILER_MSVC)
//    {
//        constexpr auto result = test();
//        ASSERT_TRUE(std::get<0>(result));
//        ASSERT_FALSE(std::get<1>(result));
//        ASSERT_FALSE(std::get<2>(result));
//        ASSERT_TRUE(std::get<3>(result));
//        ASSERT_TRUE(std::get<4>(result));
//        ASSERT_FALSE(std::get<5>(result));
//        ASSERT_TRUE(std::get<6>(result));
//        ASSERT_TRUE(std::get<7>(result));
//        ASSERT_TRUE(std::get<8>(result));
//        ASSERT_TRUE(std::get<9>(result));
//        ASSERT_TRUE(std::get<10>(result));
//        ASSERT_TRUE(std::get<11>(result));
//        ASSERT_TRUE(std::get<12>(result));
//        ASSERT_FALSE(std::get<13>(result));
//        ASSERT_FALSE(std::get<14>(result));
//    }
//#endif
}