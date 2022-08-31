#include <OSLayer/Containers/UniquePointer.h>


namespace {
    template<typename T>
    struct CustomDeleter
        : public hud::DefaultDeleter<T>
        , HUD_TEST::NonBitwiseType {

        constexpr CustomDeleter() noexcept = default;
        constexpr CustomDeleter(const CustomDeleter& other) noexcept = default;
        constexpr CustomDeleter(CustomDeleter&& other) noexcept = default;
        constexpr CustomDeleter(hud::DefaultDeleter<T>&& other) noexcept
            : hud::DefaultDeleter<T>(move(other))
            , HUD_TEST::NonBitwiseType(move(other)) {
        }
        template<typename U>
        constexpr CustomDeleter(CustomDeleter<U>&& other) noexcept
            : hud::DefaultDeleter<T>(move(other))
            , HUD_TEST::NonBitwiseType(move(other)) {
        }
        constexpr CustomDeleter& operator=(const CustomDeleter&) noexcept {
            return *this;
        }
        constexpr CustomDeleter& operator=(CustomDeleter&&) noexcept {
            return *this;
        }

    };

    using DeleterType = CustomDeleter<HUD_TEST::NonBitwiseType[]>;
}

TEST(UniquePointer_array, pointer) {

    const auto test = []() {
        i32* ptr = new i32[]{1,2};
        hud::UniquePointer<i32[]> p(ptr);
        hud::UniquePointer<i32[]> p2;
        return std::tuple{
            p.pointer() == ptr,
            p2.pointer() == nullptr
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}


TEST(UniquePointer_array, is_owning) {
    const auto test = []() {
        i32* ptr = new i32[]{ 1,2 };
        hud::UniquePointer<i32[]> p(ptr);
        hud::UniquePointer<i32[]> p2;
        return std::tuple{
            p.is_owning(),
            p2.is_owning()
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }

    // constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }
}

TEST(UniquePointer_aray, cast_bool) {
    const auto test = []() {
        i32* ptr = new i32[]{ 1,2 };
        hud::UniquePointer<i32[]> p(ptr);
        hud::UniquePointer<i32[]> p2;
        return std::tuple{
            static_cast<bool>(p),
            static_cast<bool>(p2)
        };
    };


    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }

    // constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_FALSE(std::get<1>(result));
    }
}

TEST(UniquePointer_array, operator_array) {
    const auto test = []() {
        i32* ptr = new i32[]{ 1,2 };
        hud::UniquePointer<i32[]> p(ptr);
        return std::tuple{
            p[0] == 1,
            p[1] == 2
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }

    // Constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
    }
}

TEST(UniquePointer_array, deleter) {
    const auto test = []() {
        i32 dtor_counter = 0;
        DeleterType deleter;
        deleter.set_dtor_counter_ptr(&dtor_counter);
        hud::UniquePointer < HUD_TEST::NonBitwiseType[], DeleterType > p(new HUD_TEST::NonBitwiseType[2]{ {1, nullptr}, {2, nullptr} }, deleter);
        const hud::UniquePointer<HUD_TEST::NonBitwiseType[], const DeleterType> p_const(new HUD_TEST::NonBitwiseType[2]{ {3, nullptr}, {4, nullptr} }, deleter);
        return std::tuple{
            !hud::IsConstV<hud::RemoveReferenceT<decltype(p.deleter())>>,
            hud::IsConstV<hud::RemoveReferenceT<decltype(p_const.deleter())>>,
            p.deleter().destructor_counter() == &dtor_counter,
            p_const.deleter().destructor_counter() == &dtor_counter
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }

    // constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }
}

TEST(UniquePointer_array, release) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* ptr = new HUD_TEST::NonBitwiseType[2]{ {1, nullptr}, {2, nullptr} };
        hud::UniquePointer<HUD_TEST::NonBitwiseType[]> p(ptr);
        auto released_ptr = p.leak();
        HUD_TEST::NonBitwiseType* ptr_const = new HUD_TEST::NonBitwiseType[2]{ {3, nullptr}, {4, nullptr} };
        hud::UniquePointer<const HUD_TEST::NonBitwiseType[]> p_const(ptr_const);
        auto const_released_ptr = p_const.leak();
        const auto result = std::tuple{
            hud::IsSameV<decltype(released_ptr), HUD_TEST::NonBitwiseType*>,
            hud::IsSameV<decltype(const_released_ptr), const HUD_TEST::NonBitwiseType*>,
            released_ptr == ptr,
            const_released_ptr == ptr_const
        };
        delete[] ptr;
        delete[] const_released_ptr;
        return result;
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }
}


TEST(UniquePointer_array, reset) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* ptr = new HUD_TEST::NonBitwiseType[2]{ {1, nullptr}, {2, nullptr} };
        hud::UniquePointer<HUD_TEST::NonBitwiseType[]> p(ptr);
        const bool is_not_null = p.pointer() == ptr;
        p.reset(nullptr);
        const bool is_null = p.pointer() == nullptr;
        ptr = new HUD_TEST::NonBitwiseType[2]{ {3, nullptr}, {4, nullptr} };
        p.reset(ptr);
        const bool is_not_null_2 = p.pointer() == ptr;
        p.reset();
        const bool is_null_2 = p.pointer() == nullptr;
        
        return std::tuple{
            is_not_null,
            is_null,
            is_not_null_2,
            is_null_2
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }

    // Constant
    {
        constexpr auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
    }
}

TEST(UniquePointer_array, make_unique) {
    const auto test = []() {
        hud::UniquePointer<HUD_TEST::NonBitwiseType[]> ptr = hud::make_unique<HUD_TEST::NonBitwiseType[]>(2);
        return std::tuple{
            ptr[0].constructor_count() == 0u,
            ptr[0].copy_constructor_count() == 0u,
            ptr[0].move_constructor_count() == 0u,
            ptr[0].copy_assign_count() == 0u,
            ptr[0].move_assign_count() == 0u,
            ptr[1].constructor_count() == 0u,
            ptr[1].copy_constructor_count() == 0u,
            ptr[1].move_constructor_count() == 0u,
            ptr[1].copy_assign_count() == 0u,
            ptr[1].move_assign_count() == 0u,
        };
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(std::get<0>(result));
        ASSERT_TRUE(std::get<1>(result));
        ASSERT_TRUE(std::get<2>(result));
        ASSERT_TRUE(std::get<3>(result));
        ASSERT_TRUE(std::get<4>(result));
        ASSERT_TRUE(std::get<5>(result));
        ASSERT_TRUE(std::get<6>(result));
        ASSERT_TRUE(std::get<7>(result));
        ASSERT_TRUE(std::get<8>(result));
        ASSERT_TRUE(std::get<9>(result));
    }

    // Constant ( Only when C++23 new T[]() will be allowed ) 
    // Implemented only with clang
    //{
    //    constexpr auto result = test();
    //    ASSERT_TRUE(std::get<0>(result));
    //    ASSERT_TRUE(std::get<1>(result));
    //    ASSERT_TRUE(std::get<2>(result));
    //    ASSERT_TRUE(std::get<3>(result));
    //    ASSERT_TRUE(std::get<4>(result));
    //    ASSERT_TRUE(std::get<5>(result));
    //    ASSERT_TRUE(std::get<6>(result));
    //    ASSERT_TRUE(std::get<7>(result));
    //    ASSERT_TRUE(std::get<8>(result));
    //    ASSERT_TRUE(std::get<9>(result));
    //}
}

TEST(UniquePointer_array, hash) {

    const auto test = []() {
        HUD_TEST::NonBitwiseType* ptr = new HUD_TEST::NonBitwiseType[2]{ {1, nullptr}, {2, nullptr} };
        hud::UniquePointer<HUD_TEST::NonBitwiseType[]> p(ptr);
        return hud::hash(p) == hud::hash(ptr);
    };

    // Non constant
    {
        const auto result = test();
        ASSERT_TRUE(result);
    }
}