#include <OSLayer/Traits/ApplyCV.h>

namespace {
    struct A {};
}

TEST(Traits, ApplyCV) {

    using namespace hud;
    
    ASSERT_TRUE((IsSameV<A, ApplyCVT<A, false, false>>));
    ASSERT_TRUE((IsSameV<const A, ApplyCVT<A, true, false>>));
    ASSERT_TRUE((IsSameV<volatile A, ApplyCVT<A, false, true>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<A, true, true>>));
    
    ASSERT_TRUE((IsSameV<const A, ApplyCVT<const A, false, false>>));
    ASSERT_TRUE((IsSameV<const A, ApplyCVT<const A, true, false>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const A, false, true>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const A, true, true>>));
    
    ASSERT_TRUE((IsSameV<volatile A, ApplyCVT<volatile A, false, false>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<volatile A, true, false>>));
    ASSERT_TRUE((IsSameV<volatile A, ApplyCVT<volatile A, false, true>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<volatile A, true, true>>));
    
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const volatile A, false, false>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const volatile A, true, false>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const volatile A, false, true>>));
    ASSERT_TRUE((IsSameV<const volatile A, ApplyCVT<const volatile A, true, true>>));
}