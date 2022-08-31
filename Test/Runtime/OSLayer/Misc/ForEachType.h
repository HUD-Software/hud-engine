#pragma once
#ifndef HD_INC_MISC_FOREACH_TYPE_H
#define HD_INC_MISC_FOREACH_TYPE_H
#include "TestNamespace.h"
#include <utility> // std::integer_sequence

HUD_TEST_NAMESPACE{
    template<typename... Types>
    struct for_each_type;

    template<typename T, typename... Rest>
    struct for_each_type<T, Rest...>
    {
        template< typename Functor, typename... Args>
        void operator()(Functor functor, Args&&... args)
        {
            functor.template operator() < T > (std::forward<Args>(args)...);
            if constexpr (sizeof...(Rest) > 0)
            {
                for_each_type<Rest...>()(functor, std::forward<Args>(args)...);
            }
        }
    };

    template<typename... Types, typename... Rest>
    struct for_each_type<std::tuple<Types...>, Rest...>
    {
        template<typename Functor, typename... Args>
        void operator()(Functor functor, Args&&... args)
        {
            // Iterate over each type of the tuple
            for_each_type<Types...>()(functor, std::forward<Args>(args)...);

            if constexpr (sizeof...(Rest) > 0)
            {
                for_each_type<Rest...>()(functor, std::forward<Args>(args)...);
            }
        }
    };

} // HUD_TEST_NAMESPACE

#endif // HD_INC_MISC_FOREACH_TYPE_H