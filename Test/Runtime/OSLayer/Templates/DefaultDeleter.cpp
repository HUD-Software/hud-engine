#include <OSLayer/Templates/DefaultDeleter.h>

namespace {
    enum class state {
        uninit,
        construct,
        destroyed
    };

    state A_state = state::uninit;
    struct A {
        A() { A_state = state::construct; }
        ~A() { A_state = state::destroyed; }
    };

    constexpr usize array_size = 2;
    state B_state[array_size] = { state::uninit };
    struct B {
        B() {}
        void set_index(usize idx) {
            mIndex = idx;
            B_state[mIndex] = state::construct;
        }
        ~B() { B_state[mIndex] = state::destroyed; }
        usize mIndex;
    };
}

TEST(Templates, default_deleter) {
    using namespace hud;

    /** Test DefaultDeleter */
    {
        ASSERT_EQ(A_state, state::uninit);
        A* a = new A;
        ASSERT_EQ(A_state, state::construct);
        DefaultDeleter<A> deleter_a;
        deleter_a(a);
        ASSERT_EQ(A_state, state::destroyed);


        for (usize cur = 0; cur < array_size; cur++) {
            ASSERT_EQ(B_state[cur], state::uninit);
        }
    }

    /** Test DefaultDeleter Array specialization */
    {
        B* b = new B[array_size];
        for (usize cur = 0; cur < array_size; cur++) {
            b[cur].set_index(cur);
            ASSERT_EQ(B_state[cur], state::construct);
        }

        DefaultDeleter<B[]> deleter_b;
        deleter_b(b);

        for (usize cur = 0; cur < array_size; cur++) {
            ASSERT_EQ(B_state[cur], state::destroyed);
        }
    }

    /** Test default free */
    {
        i32* c = static_cast<i32*>(Memory::allocate(sizeof(i32)));
        DefaultFree freer_c;
        freer_c(c);
    }
}