#include <OSLayer/Traits/IsConstantEvaluated.h>

namespace {
    constexpr bool evaluate() {
        if (hud::is_constant_evaluated()) {
            return true;
        }
        return false;
    }
}

TEST(Traits, IsConstantEvaluated) {
    ASSERT_FALSE(evaluate());

    constexpr bool const_evaluation = evaluate();
    ASSERT_TRUE(const_evaluation);
}