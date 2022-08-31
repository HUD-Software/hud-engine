#include <OSLayer/Traits/CommonType.h>

namespace {
    struct Base {};
    struct Derived : Base {};

    template<typename = void, typename... T>
    struct has_common_type_impl 
        : hud::FalseType {
    };

    template<typename... T>
    struct has_common_type_impl<hud::VoidT<hud::CommonTypeT<T...>>, T...>
        : hud::TrueType {
    };

    template<typename... T>
    struct has_common_type 
        : has_common_type_impl<void, T...> {
    };

    template<typename... T>
    inline constexpr bool has_common_type_v = has_common_type<T...>::Value;
}


TEST(Traits, CommonType) {
    using namespace hud;

    ASSERT_TRUE((IsSameV<CommonTypeT<i8, i16, i32>, i32>));
    ASSERT_TRUE((IsSameV<CommonTypeT<f32, f64>, f64>));
    ASSERT_TRUE((IsSameV<CommonTypeT<Derived, Base>, Base>));
    ASSERT_TRUE((IsSameV<CommonTypeT<const Derived, Base>, Base>));
    ASSERT_TRUE((IsSameV<CommonTypeT<const Derived, const Base>, Base>));
    ASSERT_TRUE((IsSameV<CommonTypeT<Derived*, Base*>, Base*>));
    ASSERT_TRUE((IsSameV<CommonTypeT<const Derived*, Base*>, const Base*>));
    ASSERT_TRUE((IsSameV<CommonTypeT<const Derived*, Derived*, const Base*>, const Base*>));
    ASSERT_TRUE((IsSameV<CommonTypeT<Derived*, const Base*>,const Base*>));
    ASSERT_TRUE((IsSameV<CommonTypeT<const i32, volatile i32>, i32>));
    ASSERT_TRUE((IsSameV<CommonTypeT<i32[], i32*>, i32*>));
    ASSERT_TRUE((IsSameV<CommonTypeT<i32[], const i32[32], i32*>, const i32*>));


    ASSERT_TRUE((has_common_type_v<i8, i16, i32>));
    ASSERT_TRUE((has_common_type_v<f32, f64>));
    ASSERT_TRUE((has_common_type_v<Derived, Base>));
    ASSERT_TRUE((has_common_type_v<const Derived, Base>));
    ASSERT_TRUE((has_common_type_v<const Derived, const Base>));
    ASSERT_TRUE((has_common_type_v<Derived*, Base*>));
    ASSERT_TRUE((has_common_type_v<const Derived*, Base*>));
    ASSERT_TRUE((has_common_type_v<const Derived*, Derived*, const Base*>));
    ASSERT_TRUE((has_common_type_v<Derived*, const Base*>));
    ASSERT_TRUE((has_common_type_v<const i32, volatile i32>));
    ASSERT_TRUE((has_common_type_v<i32[], i32*>));
    ASSERT_TRUE((has_common_type_v<i32[], const i32[32], i32*>));

    ASSERT_FALSE((has_common_type_v<i8, i16, i32, Derived>));
}