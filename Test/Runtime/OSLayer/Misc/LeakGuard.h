#pragma once
#ifndef HD_INC_TEST_MISC_LEAKGUARD_H
#define HD_INC_TEST_MISC_LEAKGUARD_H
#include "TestNamespace.h"
#include <OSLayer/Memory.h>

HUD_TEST_NAMESPACE{

template<typename T = void>
    class LeakGuard {
    public:
        constexpr LeakGuard(T* allocation) noexcept
            : ptr(allocation) {
        }

        constexpr ~LeakGuard() {
            Memory::free(ptr);
        }

        constexpr void leak() noexcept {
            ptr = nullptr;
        }
    private:
        T* ptr;
    };

    template<typename T = void>
    class LeakArrayGuard {
    public:
        constexpr LeakArrayGuard(T* allocation, const usize count) noexcept
            : ptr(allocation)
            , count_of_T(count) {
        }

        constexpr ~LeakArrayGuard() {
            Memory::free_array(ptr, count_of_T);
        }

        constexpr void leak() noexcept {
            ptr = nullptr;
            count_of_T = 0;
        }
    private:
        T* ptr;
        usize count_of_T;
    };

    class AlignLeakGuard {
    public:
        AlignLeakGuard(void* allocation) noexcept
            : ptr(allocation) {
        }

        ~AlignLeakGuard() {
            Memory::free_align(ptr);
        }

        void leak() noexcept {
            ptr = nullptr;
        }
    private:
        void* ptr;
    };

}

#endif // HD_INC_TEST_MISC_LEAKGUARD_H