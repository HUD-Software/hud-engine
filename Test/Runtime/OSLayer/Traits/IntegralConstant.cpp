#include <OSLayer/Traits/IntegralConstant.h>

TEST(Traits, IntegralConstant) {
    
    using ICT = hud::IntegralConstant<bool, true>;
    ICT ic_bool_true;
    ASSERT_TRUE(ic_bool_true.Value);
    ASSERT_TRUE(ic_bool_true());
    ASSERT_TRUE(static_cast<bool>(ic_bool_true));
    ASSERT_TRUE((hud::IsSameV<ICT::ValueType, bool>));
    ASSERT_TRUE((hud::IsSameV<ICT::Type, ICT>));

    using ICF = hud::IntegralConstant<bool, false>;
    ICF ic_bool_false;
    ASSERT_FALSE(ic_bool_false.Value);
    ASSERT_FALSE(ic_bool_false());
    ASSERT_FALSE(static_cast<bool>(ic_bool_false));
    ASSERT_TRUE((hud::IsSameV<ICF::ValueType, bool>));
    ASSERT_TRUE((hud::IsSameV<ICF::Type, ICF>));

    using ICOne = hud::IntegralConstant<i32, 1>;
    ICOne ic_int32_one;
    ASSERT_TRUE(ic_int32_one.Value);
    ASSERT_TRUE(ic_int32_one());
    ASSERT_TRUE(static_cast<bool>(ic_int32_one));
    ASSERT_TRUE((hud::IsSameV<ICOne::ValueType, i32>));
    ASSERT_TRUE((hud::IsSameV<ICOne::Type, ICOne>));

    using ICZero = hud::IntegralConstant<i32, 0>;
    ICZero ic_int32_zero;
    ASSERT_FALSE(ic_int32_zero.Value);
    ASSERT_FALSE(ic_int32_zero());
    ASSERT_FALSE(static_cast<bool>(ic_int32_zero));
    ASSERT_TRUE((hud::IsSameV<ICZero::ValueType, i32>));
    ASSERT_TRUE((hud::IsSameV<ICZero::Type, ICZero>));

    ASSERT_TRUE(hud::BoolConstant<true>::Value);
    ASSERT_FALSE(hud::BoolConstant<false>::Value);
    ASSERT_FALSE(hud::FalseType::Value);
    ASSERT_TRUE(hud::TrueType::Value);
}