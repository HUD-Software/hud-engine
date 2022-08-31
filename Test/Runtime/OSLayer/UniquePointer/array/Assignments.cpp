#include <OSLayer/Containers/UniquePointer.h>
#include <Misc/NonBitwiseType.h>

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
    using ConstDeleterType = CustomDeleter<const HUD_TEST::NonBitwiseType[]>;

    template<typename T>
    struct CustomDeleter2 : public CustomDeleter<T> {
    };
    using DeleterType2 = CustomDeleter2<HUD_TEST::NonBitwiseType[]>;
    using ConstDeleterType2 = CustomDeleter2<const HUD_TEST::NonBitwiseType[]>;
}

TEST(UniquePointer_array, assign_by_move_same_type) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* pi = new HUD_TEST::NonBitwiseType[2]{ {123, nullptr}, {456, nullptr} };
        DeleterType other_deleter;
        DeleterType deleter;
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType> other(pi, other_deleter);
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType> p(nullptr, deleter);
        
        p = hud::move(other);
        return std::tuple{
            other.pointer() == nullptr,
            p.pointer() == pi,
            other.deleter().constructor_count() == 0u,
            other.deleter().copy_constructor_count() == 1u,
            other.deleter().move_constructor_count() == 0u,
            other.deleter().copy_assign_count() == 0u,
            other.deleter().move_assign_count() == 0u,
            p.deleter().constructor_count() == 0u,
            p.deleter().copy_constructor_count() == 1u,
            p.deleter().move_constructor_count() == 0u,
            p.deleter().copy_assign_count() == 0u,
            p.deleter().move_assign_count() == 0u,
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
    }

    // Constant
    {
        constexpr auto result = test();
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
    }
}


TEST(UniquePointer_array, assign_by_move_same_type_with_deleter_ref) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* pi = new HUD_TEST::NonBitwiseType[2]{ {123, nullptr}, {456, nullptr} };
        DeleterType other_deleter;
        DeleterType deleter;
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType&> other(pi, other_deleter);
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType&> p(nullptr, deleter);
        p = hud::move(other);
        return std::tuple {
            other.pointer() == nullptr,
            p.pointer() == pi,
            &(other.deleter()) == &other_deleter,
            &(p.deleter()) == &deleter,
            other.deleter().constructor_count() == 0u,
            other.deleter().copy_constructor_count() == 0u,
            other.deleter().move_constructor_count() == 0u,
            other.deleter().copy_assign_count() == 0u,
            other.deleter().move_assign_count() == 0u,
            p.deleter().constructor_count() == 0u,
            p.deleter().copy_constructor_count() == 0u,
            p.deleter().move_constructor_count() == 0u,
            p.deleter().copy_assign_count() == 0u,
            p.deleter().move_assign_count() == 0u,
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
    }

    // Constant
    {
        constexpr auto result = test();
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
    }
}

TEST(UniquePointer_array, assign_by_move_same_type_with_different_deleter_ref) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* pi = new HUD_TEST::NonBitwiseType[2]{ {123, nullptr}, {456, nullptr} };
        DeleterType2 other_deleter;
        DeleterType deleter;
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType2&> other(pi, other_deleter);
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType&> p(nullptr, deleter);
        p = hud::move(other);
        return std::tuple{
            other.pointer() == nullptr,
            p.pointer() == pi,
            &(other.deleter()) == &other_deleter,
            &(p.deleter()) == &deleter,
            other.deleter().constructor_count() == 0u,
            other.deleter().copy_constructor_count() == 0u,
            other.deleter().move_constructor_count() == 0u,
            other.deleter().copy_assign_count() == 0u,
            other.deleter().move_assign_count() == 0u,
            p.deleter().constructor_count() == 0u,
            p.deleter().copy_constructor_count() == 0u,
            p.deleter().move_constructor_count() == 0u,
            p.deleter().copy_assign_count() == 0u,
            p.deleter().move_assign_count() == 0u,
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
    }

    // Constant
    {
        constexpr auto result = test();
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
        ASSERT_TRUE(std::get<12>(result));
        ASSERT_TRUE(std::get<13>(result));
    }
}

TEST(UniquePointer_array, assign_by_move_different_type) {
    const auto test = []() {
        HUD_TEST::NonBitwiseType* pi = new HUD_TEST::NonBitwiseType[2]{ {123, nullptr}, {456, nullptr} };
        DeleterType other_deleter;
        ConstDeleterType deleter;
        hud::UniquePointer<HUD_TEST::NonBitwiseType[], DeleterType> other(pi, other_deleter);
        hud::UniquePointer<const HUD_TEST::NonBitwiseType[], ConstDeleterType> p(nullptr, deleter);
   
        p = hud::move(other);
        return std::tuple{
            other.pointer() == nullptr,
            p.pointer() == pi,
            other.deleter().constructor_count() == 0u,
            other.deleter().copy_constructor_count() == 1u,
            other.deleter().move_constructor_count() == 0u,
            other.deleter().copy_assign_count() == 0u,
            other.deleter().move_assign_count() == 0u,
            p.deleter().constructor_count() == 0u,
            p.deleter().copy_constructor_count() == 1u,
            p.deleter().move_constructor_count() == 0u,
            p.deleter().copy_assign_count() == 0u,
            p.deleter().move_assign_count() == 0u,
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
    }

    // Constant
    {
        constexpr auto result = test();
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
        ASSERT_TRUE(std::get<10>(result));
        ASSERT_TRUE(std::get<11>(result));
    }
}