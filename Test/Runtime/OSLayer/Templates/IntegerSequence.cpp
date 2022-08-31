#include <OSLayer/Templates/IntegerSequence.h>

TEST(Templates, IntegerSequence) {
    using namespace hud;

    IntegerSequence<i32, 1, 2, 3, 16, 32> seq;
    ASSERT_EQ(seq.size(), 5u);

    using Seq1T = CatIntegerSequenceT<IntegerSequence<i8, 1, 2>>;
    Seq1T seq1;
    constexpr bool seq1_same_type = IsSameV<Seq1T::Type, i8>;
    ASSERT_TRUE(seq1_same_type);
    ASSERT_EQ(seq1.size(), 2u);

    using Seq2T = CatIntegerSequenceT<IntegerSequence<i8, 1, 2>, IntegerSequence<i8, 3, 4, 5>>;
    Seq2T seq2;
    constexpr bool seq2_same_type = IsSameV<Seq2T::Type, i8>;
    ASSERT_TRUE(seq2_same_type);
    ASSERT_EQ(seq2.size(), 5u);

    using Seq3T = CatIntegerSequenceT<IntegerSequence<i8, 1, 2>, IntegerSequence<i8, 3, 4, 5>, IntegerSequence<i8, 6, 7, 8>>;
    Seq3T seq3;
    constexpr bool seq3_same_type = IsSameV<Seq3T::Type, i8>;
    ASSERT_TRUE(seq3_same_type);
    ASSERT_EQ(seq3.size(), 8u);

    using Seq4T = CatIntegerSequenceT<IntegerSequence<i8, 1, 2>, IntegerSequence<i32, 3, 4, 5>, IntegerSequence<usize, 6, 7, 8, 7>>;
    Seq4T seq4;
    constexpr bool seq4_same_type = IsSameV<Seq4T::Type, usize>;
    ASSERT_TRUE(seq4_same_type);
    ASSERT_EQ(seq4.size(), 9u);
}