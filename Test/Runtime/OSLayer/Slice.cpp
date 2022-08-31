#include <OSLayer/Slice.h>
#include <OSLayer/Templates/Swap.h>

TEST(Slice, default_constructor) {
    using namespace hud;

    // constexpr Slice() noexcept
    Slice<i32> slice;
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Slice, constructor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    // constexpr Slice(T* first, usize count) noexcept
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
}

TEST(Slice, copy_constructor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    // Slice(const Slice& other) noexcept
    Slice<i32> copy(slice);
    ASSERT_EQ(copy.data(), arr);
    ASSERT_FALSE(copy.is_empty());
    ASSERT_EQ(copy.count(), 4u);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
}

TEST(Slice, move_constructor) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    // constexpr Slice(Slice&& other) noexcept
    Slice<i32> moved(move(slice));
    ASSERT_EQ(moved.data(), arr);
    ASSERT_FALSE(moved.is_empty());
    ASSERT_EQ(moved.count(), 4u);
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Slice, copy_assignment) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };

    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    Slice<i32> copy;
    ASSERT_EQ(copy.data(), nullptr);
    ASSERT_TRUE(copy.is_empty());
    ASSERT_EQ(copy.count(), 0u);
    {
        // Slice& operator=(const Slice& other) noexcept
        copy = slice;
        ASSERT_EQ(copy.data(), arr);
        ASSERT_FALSE(copy.is_empty());
        ASSERT_EQ(copy.count(), 4u);
        ASSERT_EQ(slice.data(), arr);
        ASSERT_FALSE(slice.is_empty());
        ASSERT_EQ(slice.count(), 4u);
    }
}

TEST(Slice, move_assignment) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };

    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    Slice<i32> copy;
    ASSERT_EQ(copy.data(), nullptr);
    ASSERT_TRUE(copy.is_empty());
    ASSERT_EQ(copy.count(), 0u);
    {
        // constexpr Slice& operator=(Slice&& other) noexcept
        copy = move(slice);
        ASSERT_EQ(copy.data(), arr);
        ASSERT_FALSE(copy.is_empty());
        ASSERT_EQ(copy.count(), 4u);
        ASSERT_EQ(slice.data(), nullptr);
        ASSERT_TRUE(slice.is_empty());
        ASSERT_EQ(slice.count(), 0u);
    }
}

TEST(Slice, reset) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);

    // void reset() noexcept
    slice.reset();

    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Slice, operator_indexed_accessor) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };

    // constexpr AddLValueReferenceT<T> operator[](const index at) noexcept
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
    ASSERT_EQ(slice[0], 10);
    ASSERT_EQ(slice[1], 20);
    ASSERT_EQ(slice[2], 30);
    ASSERT_EQ(slice[3], 40);

    // constexpr AddConstT<AddLValueReferenceT<T>> operator[](const index at) const noexcept
    const Slice<i32> slice2(arr, 4);
    ASSERT_EQ(slice2.data(), arr);
    ASSERT_FALSE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 4u);
    ASSERT_EQ(slice2[0], 10);
    ASSERT_EQ(slice2[1], 20);
    ASSERT_EQ(slice2[2], 30);
    ASSERT_EQ(slice2[3], 40);
}

TEST(Slice, is_empty) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    Slice<i32> empty;
    ASSERT_FALSE(slice.is_empty());
    ASSERT_TRUE(empty.is_empty());
}

TEST(Slice, data) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    Slice<i32> slice2;
    ASSERT_EQ(slice.data(), &arr[0]);
    ASSERT_EQ(slice2.data(), nullptr);
}

TEST(Slice, count) {
    using namespace hud; 
    
    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    Slice<i32> slice2;
    ASSERT_EQ(slice.count(), 4u);
    ASSERT_EQ(slice2.count(), 0u);
}

TEST(Slice, byte_count) {
    i32 arr[4] = { 10,20,30,40 };
    hud::Slice<i32> slice(arr, 4);
    hud::Slice<i32> slice2;
    ASSERT_EQ(slice.byte_count(), 4u * sizeof(i32));
    ASSERT_EQ(slice2.byte_count(), 0u * sizeof(i32));
}

TEST(Slice, sub_slice) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), &arr[0]);
    ASSERT_EQ(slice.count(), 4u);

    // sub_slice of whole slice
    {
        Slice<i32> sub_slice(slice.sub_slice(0, slice.count()));
        ASSERT_EQ(slice.data(), &arr[0]);
        ASSERT_EQ(slice.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[0]);
        ASSERT_EQ(sub_slice.count(), 4u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &slice[idx]);
        }
        ASSERT_EQ(idx, 4u);
    }

    // sub_slice of nothing
    {
        Slice<i32> sub_slice(slice.sub_slice(0, 0));
        ASSERT_EQ(slice.data(), &arr[0]);
        ASSERT_EQ(slice.count(), 4u);
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
        Slice<i32> sub_slice(slice.sub_slice(0, slice.count() / 2));
        ASSERT_EQ(slice.data(), &arr[0]);
        ASSERT_EQ(slice.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[0]);
        ASSERT_EQ(sub_slice.count(), 2u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &slice[idx]);
        }
        ASSERT_EQ(idx, 2u);
    }

    // sub_slice of last part of sequence
    {
        Slice<i32> sub_slice(slice.sub_slice(slice.count() / 2, slice.count() / 2)); // sub slice from half to half end
        ASSERT_EQ(slice.data(), &arr[0]);
        ASSERT_EQ(slice.count(), 4u);
        ASSERT_EQ(sub_slice.data(), &arr[2]);
        ASSERT_EQ(sub_slice.count(), 2u);

        // Additional test when iterating on the sub_slice
        usize idx = 0;
        for (; idx < sub_slice.count(); idx++) {
            ASSERT_EQ(&sub_slice[idx], &slice[idx + slice.count() / 2]);
        }
        ASSERT_EQ(idx, 2u);
    }
}

TEST(Slice, swap) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.data(), arr);
    ASSERT_FALSE(slice.is_empty());
    ASSERT_EQ(slice.count(), 4u);
    Slice<i32> slice2;
    ASSERT_EQ(slice2.data(), nullptr);
    ASSERT_TRUE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 0u);

    // constexpr void swap(Slice& other) noexcept 
    hud::swap(slice, slice2);
    ASSERT_EQ(slice2.data(), arr);
    ASSERT_FALSE(slice2.is_empty());
    ASSERT_EQ(slice2.count(), 4u);
    ASSERT_EQ(slice.data(), nullptr);
    ASSERT_TRUE(slice.is_empty());
    ASSERT_EQ(slice.count(), 0u);
}

TEST(Slice, iterators) {
    using namespace hud;

    // constexpr Iterator begin() noexcept
    // constexpr Iterator end() noexcept
    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);
    ASSERT_EQ(slice.begin(), &arr[0]);
    ASSERT_EQ(slice.end(), &arr[4]);
    ASSERT_EQ(*slice.begin(), 10);
    ASSERT_EQ(*(slice.end() - 1), 40);
    ASSERT_EQ(slice.end() - slice.begin(), static_cast<isize>(slice.count()));

    // constexpr ConstIterator begin() const noexcept
    // constexpr ConstIterator end() const noexcept
    const Slice<i32> slice_const(arr, 4);
    ASSERT_EQ(slice_const.begin(), &arr[0]);
    ASSERT_EQ(slice_const.end(), &arr[4]);
    ASSERT_EQ(*slice_const.begin(), 10);
    ASSERT_EQ(*(slice_const.end() - 1), 40);
    ASSERT_EQ(slice_const.end() - slice_const.begin(), static_cast<isize>(slice.count()));
}

TEST(Slice, range_for_loop) {
    using namespace hud;

    i32 arr[4] = { 10,20,30,40 };
    Slice<i32> slice(arr, 4);

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

    const Slice<i32>& slice_const = slice;
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