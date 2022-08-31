#include <OSLayer/Allocators/Allocation.h>
#include <OSLayer/Templates/Swap.h>

TEST(Allocation, default_constructor) {
    using namespace hud;

    // constexpr Allocation() noexcept
    Allocation<i32 > slice;
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Allocation, constructor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    // constexpr Allocation(T* first, usize count) noexcept
    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
}

TEST(Allocation, copy_constructor) {
    ASSERT_FALSE((hud::IsCopyConstructibleV<hud::Allocation<i32>>));
}

TEST(Allocation, move_constructor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    // constexpr Allocation(Allocation&& other) noexcept
    Allocation<i32> moved(move(slice));
    ASSERT_EQ(moved.data(), arr);
    ASSERT_FALSE(moved.is_empty());
    ASSERT_EQ(moved.count(), 4u);
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}


TEST(Allocation, copy_assignment) {
    ASSERT_FALSE((hud::IsCopyAssignableV<hud::Allocation<i32>>));
}

TEST(Allocation, move_assignment) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    Allocation<i32> copy;
    ASSERT_EQ(copy.data(), nullptr);
    ASSERT_TRUE(copy.is_empty());
    ASSERT_EQ(copy.count(), 0u);
    {
        // constexpr Allocation& operator=(Allocation&& other) noexcept
        copy = move(slice);
        ASSERT_EQ(copy.data(), arr);
        ASSERT_FALSE(copy.is_empty());
        ASSERT_EQ(copy.count(), 4u);
        ASSERT_EQ(slice.data(), nullptr);
        ASSERT_TRUE(slice.is_empty());
        ASSERT_EQ(slice.count(), 0u);
    }
}

TEST(Allocation, reset) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    // void reset() noexcept
    slice.leak();

    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Allocation, operator_indexed_accessor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    // constexpr AddLValueReferenceT<T> operator[](const index at) noexcept
    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
    ASSERT_EQ(slice[0], 10);
    ASSERT_EQ(slice[1], 20);
    ASSERT_EQ(slice[2], 30);
    ASSERT_EQ(slice[3], 40);

    // constexpr AddConstT<AddLValueReferenceT<T>> operator[](const index at) const noexcept
    const Allocation<i32> slice2(arr, 4);
    ASSERT_EQ(slice2.data(), arr);
    ASSERT_FALSE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 4u);
    ASSERT_EQ(slice2[0], 10);
    ASSERT_EQ(slice2[1], 20);
    ASSERT_EQ(slice2[2], 30);
    ASSERT_EQ(slice2[3], 40);
}

TEST(Allocation, is_empty) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    Allocation<i32> empty;
    ASSERT_FALSE(slice.is_empty());
    ASSERT_TRUE(empty.is_empty());
}

TEST(Allocation, data) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    Allocation<i32> slice2;
    ASSERT_EQ(slice.data(), &arr[0]);
    ASSERT_EQ(slice2.data(), nullptr);
}

TEST(Allocation, data_at) {

    i32 arr[4] = { 10,20,30,40 };
    hud::Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data_at(0u), &arr[0]);
    ASSERT_EQ(slice.data_at(1u), &arr[1]);
    ASSERT_EQ(slice.data_at(2u), &arr[2]);
    ASSERT_EQ(slice.data_at(3u), &arr[3]);
}

TEST(Allocation, count) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    Allocation<i32> slice2;
    ASSERT_EQ(slice.count(), 4u);
    ASSERT_EQ(slice2.count(), 0u);
}

TEST(Allocation, byte_count) {
    i32 arr[4] = { 10,20,30,40 };
    hud::Allocation<i32> slice(arr, 4);
    hud::Allocation<i32> slice2;
    ASSERT_EQ(slice.byte_count(), 4u*sizeof(i32));
    ASSERT_EQ(slice2.byte_count(), 0u * sizeof(i32));
}

TEST(Allocation, sub_slice) {

    i32 arr[4] = { 10,20,30,40 };
    hud::Allocation<i32> allocation(arr, 4);
    ASSERT_EQ(allocation.data(), &arr[0]);
    ASSERT_EQ(allocation.count(), 4u);

    // sub_slice of whole slice
    {
        hud::Slice<i32> sub_slice(allocation.sub_slice(0, allocation.count()));
        ASSERT_EQ(allocation.data(), &arr[0]);
        ASSERT_EQ(allocation.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[0]);
        ASSERT_EQ(sub_slice.count(), 4u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &allocation[idx]);
        }
        ASSERT_EQ(idx, 4u);
    }

    // sub_slice of nothing
    {
        hud::Slice<i32> sub_slice(allocation.sub_slice(0, 0));
        ASSERT_EQ(allocation.data(), &arr[0]);
        ASSERT_EQ(allocation.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[0]);
        ASSERT_EQ(sub_slice.count(), 0u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_FALSE(false); // Must be empty sub_slice
        }
        ASSERT_EQ(idx, sub_slice.count());
    }

    // sub_slice of first part of sequence
    {
        hud::Slice<i32> sub_slice(allocation.sub_slice(0, allocation.count() / 2));
        ASSERT_EQ(allocation.data(), &arr[0]);
        ASSERT_EQ(allocation.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[0]);
        ASSERT_EQ(sub_slice.count(), 2u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &allocation[idx]);
        }
        ASSERT_EQ(idx, 2u);
    }

    // sub_slice of last part of sequence
    {
        hud::Slice<i32> sub_slice(allocation.sub_slice(allocation.count() / 2, allocation.count() / 2)); // sub slice from half to half end
        ASSERT_EQ(allocation.data(), &arr[0]);
        ASSERT_EQ(allocation.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[2]);
        ASSERT_EQ(sub_slice.count(), 2u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &allocation[idx + allocation.count() / 2]);
        }
        ASSERT_EQ(idx, 2u);
    }
}

TEST(Allocation, to_slice) {

    // to_slice of empty allocation is empty slice
    {
        hud::Allocation<i32> allocation(nullptr, 0u);
        ASSERT_EQ(allocation.data(), nullptr);
        ASSERT_EQ(allocation.count(), 0u);

        hud::Slice<i32> slice(allocation.to_slice());
        ASSERT_EQ(slice.data(), allocation.data());
        ASSERT_EQ(slice.count(), allocation.count());
    }

    // to_slice of non empty allocation is Slice over the whole allocation.
    {
        i32 arr[4] = { 10,20,30,40 };
        hud::Allocation<i32> allocation(arr, 4u);
        ASSERT_EQ(allocation.data(), &arr[0]);
        ASSERT_EQ(allocation.count(), 4u);

        hud::Slice<i32> slice(allocation.to_slice());
        ASSERT_EQ(slice.data(), allocation.data());
        ASSERT_EQ(slice.count(), allocation.count());
    }
}

TEST(Allocation, swap) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
    Allocation<i32> slice2;
    ASSERT_EQ(slice2.data(), nullptr);
    ASSERT_TRUE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 0u);

    // constexpr void swap(Allocation& other) noexcept 
    hud::swap(slice, slice2);
    ASSERT_EQ(slice2.data(), arr);
    ASSERT_FALSE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 4u);
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Allocation, iterators) {
    using namespace hud;

    // constexpr Iterator begin() noexcept
    // constexpr Iterator end() noexcept
    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);
    ASSERT_EQ(slice.begin(), &arr[0]);
    ASSERT_EQ(slice.end(), &arr[4]);
    ASSERT_EQ(*slice.begin(), 10);
    ASSERT_EQ(*(slice.end() - 1), 40);
    ASSERT_EQ(slice.end() - slice.begin(), static_cast<isize>(slice.count()));

    // constexpr ConstIterator begin() const noexcept
    // constexpr ConstIterator end() const noexcept
    const Allocation<i32> slice_const(arr, 4);
    ASSERT_EQ(slice_const.begin(), &arr[0]);
    ASSERT_EQ(slice_const.end(), &arr[4]);
    ASSERT_EQ(*slice_const.begin(), 10);
    ASSERT_EQ(*(slice_const.end() - 1), 40);
    ASSERT_EQ(slice_const.end() - slice_const.begin(), static_cast<isize>(slice.count()));
}

TEST(Allocation, range_for_loop) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Allocation<i32> slice(arr, 4);

    i32 result[4];
    i32 index = 0;
    // constexpr Iterator begin() noexcept
    // constexpr Iterator end() noexcept
    for (auto& value : slice) {
        result[index++] = value;
    }
    ASSERT_EQ(result[0], arr[0]);
    ASSERT_EQ(result[1], arr[1]);
    ASSERT_EQ(result[2], arr[2]);
    ASSERT_EQ(result[3], arr[3]);

    const Allocation<i32>& slice_const = slice;
    index = 0;
    Memory::set_zero(result);

    // constexpr ConstIterator begin() const noexcept
    // constexpr ConstIterator end() const noexcept
    for (auto& value : slice_const) {
        result[index++] = value;
    }
    ASSERT_EQ(result[0], arr[0]);
    ASSERT_EQ(result[1], arr[1]);
    ASSERT_EQ(result[2], arr[2]);
    ASSERT_EQ(result[3], arr[3]);
}