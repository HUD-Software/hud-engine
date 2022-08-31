#pragma once
#ifndef HD_INC_MISC_FOREACH_VALUE_H
#define HD_INC_MISC_FOREACH_VALUE_H
#include "TestNamespace.h"
#include <utility> // std::integer_sequence

HUD_TEST_NAMESPACE{
    template<typename T, T... seq>
    struct for_each_value;
    
    template<typename T, T current, T...seq>
    struct for_each_value<T, current, seq...>
    {
        template< typename Functor>
        void operator()(Functor functor)
        {
            functor.template operator()<current>();
            if constexpr(sizeof...(seq) > 0)
            {
                for_each_value<T, seq...>()(functor);
            }
        }
    };

    template<typename T, T current, T... seq>
    struct for_each_value<std::integer_sequence<T, current, seq...>> : public for_each_value<T, current, seq...>
    {};

} // HUD_TEST_NAMESPACE
#endif // HD_INC_MISC_FOREACH_VALUE_H