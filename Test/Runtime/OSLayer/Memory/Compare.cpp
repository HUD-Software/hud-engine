#include <OSLayer/Memory.h>

TEST(Memory, compare_pointer_to_buffer) {

    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8 *lhs, const u8 *rhs1, const u8 *rhs2, const u8 *rhs3, const u8 *rhs4) -> std::tuple<i32, i32, i32, i32> {
        return {
            Memory::compare(lhs, rhs1, 3 * sizeof(u8)),
            Memory::compare(lhs, rhs2, 3 * sizeof(u8)),
            Memory::compare(lhs, rhs3, 3 * sizeof(u8)),
            Memory::compare(lhs, rhs4, 3 * sizeof(u8))
        };
    };

    // Non constant
    {
        std::tuple<i32, i32, i32, i32> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf), 0);
        ASSERT_GT(std::get<1>(result_buf), 0);
        ASSERT_EQ(std::get<2>(result_buf), 0);
        ASSERT_LE(std::get<3>(result_buf), 0);

        std::tuple<i32, i32, i32, i32> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_LE(std::get<0>(result_buf_2), 0);
        ASSERT_EQ(std::get<1>(result_buf_2), 0);
        ASSERT_LE(std::get<2>(result_buf_2), 0);
        ASSERT_LE(std::get<3>(result_buf_2), 0);

        std::tuple<i32, i32, i32, i32> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf_3), 0);
        ASSERT_GT(std::get<1>(result_buf_3), 0);
        ASSERT_EQ(std::get<2>(result_buf_3), 0);
        ASSERT_LE(std::get<3>(result_buf_3), 0);

        std::tuple<i32, i32, i32, i32> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_GT(std::get<0>(result_buf_4), 0);
        ASSERT_GT(std::get<1>(result_buf_4), 0);
        ASSERT_GT(std::get<2>(result_buf_4), 0);
        ASSERT_EQ(std::get<3>(result_buf_4), 0);
    }

    // Constant
    {
        constexpr std::tuple<i32, i32, i32, i32> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf), 0);
        ASSERT_GT(std::get<1>(result_buf), 0);
        ASSERT_EQ(std::get<2>(result_buf), 0);
        ASSERT_LE(std::get<3>(result_buf), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_LE(std::get<0>(result_buf_2), 0);
        ASSERT_EQ(std::get<1>(result_buf_2), 0);
        ASSERT_LE(std::get<2>(result_buf_2), 0);
        ASSERT_LE(std::get<3>(result_buf_2), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf_3), 0);
        ASSERT_GT(std::get<1>(result_buf_3), 0);
        ASSERT_EQ(std::get<2>(result_buf_3), 0);
        ASSERT_LE(std::get<3>(result_buf_3), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_GT(std::get<0>(result_buf_4), 0);
        ASSERT_GT(std::get<1>(result_buf_4), 0);
        ASSERT_GT(std::get<2>(result_buf_4), 0);
        ASSERT_EQ(std::get<3>(result_buf_4), 0);
    }
}

TEST(Memory, compare_C_buffer) {

    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8(&lhs)[3], const u8(&rhs1)[3], const u8(&rhs2)[3], const u8(&rhs3)[3], const u8(&rhs4)[3]) -> std::tuple<i32, i32, i32, i32> {
        return {
            Memory::compare(lhs, rhs1),
            Memory::compare(lhs, rhs2),
            Memory::compare(lhs, rhs3),
            Memory::compare(lhs, rhs4)
        };
    };

    // Non constant
    {
        std::tuple<i32, i32, i32, i32> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf), 0);
        ASSERT_GT(std::get<1>(result_buf), 0);
        ASSERT_EQ(std::get<2>(result_buf), 0);
        ASSERT_LE(std::get<3>(result_buf), 0);

        std::tuple<i32, i32, i32, i32> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_LE(std::get<0>(result_buf_2), 0);
        ASSERT_EQ(std::get<1>(result_buf_2), 0);
        ASSERT_LE(std::get<2>(result_buf_2), 0);
        ASSERT_LE(std::get<3>(result_buf_2), 0);

        std::tuple<i32, i32, i32, i32> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf_3), 0);
        ASSERT_GT(std::get<1>(result_buf_3), 0);
        ASSERT_EQ(std::get<2>(result_buf_3), 0);
        ASSERT_LE(std::get<3>(result_buf_3), 0);

        std::tuple<i32, i32, i32, i32> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_GT(std::get<0>(result_buf_4), 0);
        ASSERT_GT(std::get<1>(result_buf_4), 0);
        ASSERT_GT(std::get<2>(result_buf_4), 0);
        ASSERT_EQ(std::get<3>(result_buf_4), 0);
    }

    // Constant
    {
        constexpr std::tuple<i32, i32, i32, i32> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf), 0);
        ASSERT_GT(std::get<1>(result_buf), 0);
        ASSERT_EQ(std::get<2>(result_buf), 0);
        ASSERT_LE(std::get<3>(result_buf), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_LE(std::get<0>(result_buf_2), 0);
        ASSERT_EQ(std::get<1>(result_buf_2), 0);
        ASSERT_LE(std::get<2>(result_buf_2), 0);
        ASSERT_LE(std::get<3>(result_buf_2), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_EQ(std::get<0>(result_buf_3), 0);
        ASSERT_GT(std::get<1>(result_buf_3), 0);
        ASSERT_EQ(std::get<2>(result_buf_3), 0);
        ASSERT_LE(std::get<3>(result_buf_3), 0);

        constexpr std::tuple<i32, i32, i32, i32> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_GT(std::get<0>(result_buf_4), 0);
        ASSERT_GT(std::get<1>(result_buf_4), 0);
        ASSERT_GT(std::get<2>(result_buf_4), 0);
        ASSERT_EQ(std::get<3>(result_buf_4), 0);
    }
}

TEST(Memory, compare_equal_pointer_to_buffer)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8* lhs, const u8* rhs1, const u8* rhs2, const u8* rhs3, const u8* rhs4) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_equal(lhs, rhs1, 3 * sizeof(u8)),
            Memory::compare_equal(lhs, rhs2, 3 * sizeof(u8)),
            Memory::compare_equal(lhs, rhs3, 3 * sizeof(u8)),
            Memory::compare_equal(lhs, rhs4, 3 * sizeof(u8))
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_TRUE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_TRUE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_TRUE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_TRUE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_TRUE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_TRUE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_TRUE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_TRUE(std::get<3>(result_buf_4));
    }
}

TEST(Memory, compare_equal_C_buffer)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8(&lhs)[3], const u8(&rhs1)[3], const u8(&rhs2)[3], const u8(&rhs3)[3], const u8(&rhs4)[3]) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_equal(lhs, rhs1),
            Memory::compare_equal(lhs, rhs2),
            Memory::compare_equal(lhs, rhs3),
            Memory::compare_equal(lhs, rhs4)
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_TRUE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_TRUE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_TRUE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_TRUE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_TRUE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_TRUE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_TRUE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_TRUE(std::get<3>(result_buf_4));
    }
}

TEST(Memory, compare_less_pointer_to_buffer)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8* lhs, const u8* rhs1, const u8* rhs2, const u8* rhs3, const u8* rhs4) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_less(lhs, rhs1, 3 * sizeof(u8)),
            Memory::compare_less(lhs, rhs2, 3 * sizeof(u8)),
            Memory::compare_less(lhs, rhs3, 3 * sizeof(u8)),
            Memory::compare_less(lhs, rhs4, 3 * sizeof(u8))
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_TRUE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_TRUE(std::get<2>(result_buf_2));
        ASSERT_TRUE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_TRUE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_TRUE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_TRUE(std::get<2>(result_buf_2));
        ASSERT_TRUE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_TRUE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }
}

TEST(Memory, compare_less_C_array)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8(&lhs)[3], const u8(&rhs1)[3], const u8(&rhs2)[3], const u8(&rhs3)[3], const u8(&rhs4)[3]) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_less(lhs, rhs1),
            Memory::compare_less(lhs, rhs2),
            Memory::compare_less(lhs, rhs3),
            Memory::compare_less(lhs, rhs4)
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_TRUE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_TRUE(std::get<2>(result_buf_2));
        ASSERT_TRUE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_TRUE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_FALSE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_TRUE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_TRUE(std::get<2>(result_buf_2));
        ASSERT_TRUE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_FALSE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_TRUE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_4));
        ASSERT_FALSE(std::get<1>(result_buf_4));
        ASSERT_FALSE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }
}


TEST(Memory, compare_greater_pointer_to_buffer)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8* lhs, const u8* rhs1, const u8* rhs2, const u8* rhs3, const u8* rhs4) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_greater(lhs, rhs1, 3 * sizeof(u8)),
            Memory::compare_greater(lhs, rhs2, 3 * sizeof(u8)),
            Memory::compare_greater(lhs, rhs3, 3 * sizeof(u8)),
            Memory::compare_greater(lhs, rhs4, 3 * sizeof(u8))
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_TRUE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_TRUE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_4));
        ASSERT_TRUE(std::get<1>(result_buf_4));
        ASSERT_TRUE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_TRUE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_TRUE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_4));
        ASSERT_TRUE(std::get<1>(result_buf_4));
        ASSERT_TRUE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }
}

TEST(Memory, compare_greater_C_array)
{
    using namespace hud;

    constexpr u8 buf[3] = { 2, 4, 8 };
    constexpr u8 buf_2[3] = { 2, 4, 7 };
    constexpr u8 buf_3[3] = { 2, 4, 8 };
    constexpr u8 buf_4[3] = { 2, 4, 9 };

    auto test = [](const u8(&lhs)[3], const u8(&rhs1)[3], const u8(&rhs2)[3], const u8(&rhs3)[3], const u8(&rhs4)[3]) -> std::tuple<bool, bool, bool, bool> {
        return {
            Memory::compare_greater(lhs, rhs1),
            Memory::compare_greater(lhs, rhs2),
            Memory::compare_greater(lhs, rhs3),
            Memory::compare_greater(lhs, rhs4)
        };
    };

    // Non constant
    {
        std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_TRUE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_TRUE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_4));
        ASSERT_TRUE(std::get<1>(result_buf_4));
        ASSERT_TRUE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }

    // Constant
    {
        constexpr std::tuple<bool, bool, bool, bool> result_buf = test(buf, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf));
        ASSERT_TRUE(std::get<1>(result_buf));
        ASSERT_FALSE(std::get<2>(result_buf));
        ASSERT_FALSE(std::get<3>(result_buf));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_2 = test(buf_2, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_2));
        ASSERT_FALSE(std::get<1>(result_buf_2));
        ASSERT_FALSE(std::get<2>(result_buf_2));
        ASSERT_FALSE(std::get<3>(result_buf_2));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_3 = test(buf_3, buf, buf_2, buf_3, buf_4);
        ASSERT_FALSE(std::get<0>(result_buf_3));
        ASSERT_TRUE(std::get<1>(result_buf_3));
        ASSERT_FALSE(std::get<2>(result_buf_3));
        ASSERT_FALSE(std::get<3>(result_buf_3));

        constexpr std::tuple<bool, bool, bool, bool> result_buf_4 = test(buf_4, buf, buf_2, buf_3, buf_4);
        ASSERT_TRUE(std::get<0>(result_buf_4));
        ASSERT_TRUE(std::get<1>(result_buf_4));
        ASSERT_TRUE(std::get<2>(result_buf_4));
        ASSERT_FALSE(std::get<3>(result_buf_4));
    }
}