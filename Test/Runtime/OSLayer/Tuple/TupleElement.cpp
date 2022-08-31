#include <OSLayer/Containers/TupleElement.h>
#include <OSLayer/Containers/Tuple.h>

namespace {
    template<const usize at, typename T0, typename T1>
    struct TupleLikeClass;

    template<typename T0, typename T1>
    struct TupleLikeClass<0, T0, T1> {
        using Type = T0;
        Type element;
    };

    template<typename T0, typename T1>
    struct TupleLikeClass<1, T0, T1> {
        using Type = T1;
        Type element;
    };
}


namespace hud {
    /**
    Specialization to retrieve the type of the TupleLikeClass that correspond to the given template argument
    */
    template<typename T0, typename T1>
    struct TupleElement< 0, TupleLikeClass<0, T0, T1>> {
        using Type = typename TupleLikeClass<0, T0, T1>::Type;
    };
    template<typename T0, typename T1>
    struct TupleElement< 1, TupleLikeClass<1, T0, T1>> {
        using Type = typename TupleLikeClass<1, T0, T1>::Type;
    };
}

TEST(Tuple, TupleElement) {

    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<0, hud::Tuple<u32, u64, wchar> >, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<1, hud::Tuple<u32, u64, wchar> >, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<2, hud::Tuple<u32, u64, wchar> >, wchar>));

    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<0, TupleLikeClass<0, u32, u64>>, u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, TupleLikeClass<0, u32, u64>>, u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, TupleLikeClass<1, u32, u64>>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<1, TupleLikeClass<1, u32, u64>>, u64>));

    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const TupleLikeClass<0, u32, u64>>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<0, const TupleLikeClass<0, u32, u64>>, const u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const TupleLikeClass<0, u32, u64>>, u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const TupleLikeClass<0, u32, u64>>, const u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const TupleLikeClass<1, u32, u64>>, u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const TupleLikeClass<1, u32, u64>>, const u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const TupleLikeClass<1, u32, u64>>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<1, const TupleLikeClass<1, u32, u64>>, const u64>));

    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, volatile TupleLikeClass<0, u32, u64>>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<0, volatile TupleLikeClass<0, u32, u64>>, volatile u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, volatile TupleLikeClass<0, u32, u64>>, u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, volatile TupleLikeClass<0, u32, u64>>, volatile u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, volatile TupleLikeClass<1, u32, u64>>, u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, volatile TupleLikeClass<1, u32, u64>>, volatile u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, volatile TupleLikeClass<1, u32, u64>>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<1, volatile TupleLikeClass<1, u32, u64>>, volatile u64>));


    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const volatile TupleLikeClass<0, u32, u64>>, u32>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<0, const volatile TupleLikeClass<0, u32, u64>>, const volatile u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const volatile TupleLikeClass<0, u32, u64>>, u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<0, const volatile TupleLikeClass<0, u32, u64>>, const volatile u64>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const volatile TupleLikeClass<1, u32, u64>>, u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const volatile TupleLikeClass<1, u32, u64>>, const volatile u32>));
    ASSERT_FALSE((hud::IsSameV<hud::TupleElementT<1, const volatile TupleLikeClass<1, u32, u64>>, u64>));
    ASSERT_TRUE((hud::IsSameV<hud::TupleElementT<1, const volatile TupleLikeClass<1, u32, u64>>, const volatile u64>));
}