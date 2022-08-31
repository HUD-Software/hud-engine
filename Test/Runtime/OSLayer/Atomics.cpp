#include <OSLayer/Atomics.h>
#include <atomic>
TEST(Atomics, thread_fence)
{
    using namespace hud;
    // Test nothong, just be sure it compile
    Atomics::thread_fence(Atomics::EMemoryOrder::relaxed);
    Atomics::thread_fence(Atomics::EMemoryOrder::consume);
    Atomics::thread_fence(Atomics::EMemoryOrder::acquire);
    Atomics::thread_fence(Atomics::EMemoryOrder::release);
    Atomics::thread_fence(Atomics::EMemoryOrder::acq_rel);
    Atomics::thread_fence(Atomics::EMemoryOrder::seq_cst);
}

TEST(Atomics, load_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        alignas(sizeof(T)) T storage = static_cast<T>(32);

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(Atomics::load(storage), static_cast<T>(32));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::relaxed), static_cast<T>(32));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::consume), static_cast<T>(32));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::acquire), static_cast<T>(32));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::seq_cst), static_cast<T>(32));
    });
}

TEST(Atomics, load_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        T* storage = reinterpret_cast<T*>(0x32323232);

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(Atomics::load(storage), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(Atomics::load(storage, Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(0x32323232));
    });
}

TEST(Atomics, store_integral)
{
    using namespace hud;
    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{};
        alignas(sizeof(T)) T storage = default_value;

        // Be sure we really test different value
        ASSERT_EQ(storage, default_value);
        ASSERT_NE(storage, value);

        Atomics::store(storage, value);
        ASSERT_EQ(storage, value);
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(storage, value);
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(storage, value);
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(storage, value);
    });
}


TEST(Atomics, store_pointer)
{
    using namespace hud;
    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const default_value = nullptr;
        T* storage = nullptr;

        // Be sure we really test different value
        ASSERT_EQ(storage, default_value);
        ASSERT_NE(storage, value);

        Atomics::store(storage, value);
        ASSERT_EQ(storage, reinterpret_cast<T*>(0x32323232));
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(storage, reinterpret_cast<T*>(0x32323232));
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(storage, reinterpret_cast<T*>(0x32323232));
        storage = default_value;

        Atomics::store(storage, value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(storage, reinterpret_cast<T*>(0x32323232));
    });
}

TEST(Atomics, compare_and_swap_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{};
        constexpr const T expected = T{};
        alignas(sizeof(T)) T destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::relaxed), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::relaxed), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::consume), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::consume), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acquire), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acquire), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::release), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::release), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acq_rel), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acq_rel), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::seq_cst), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::seq_cst), destination);
        ASSERT_EQ(destination, value);
    });
}


TEST(Atomics, compare_and_swap_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        constexpr T* const expected = nullptr;
        T* destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::relaxed), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::relaxed), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::consume), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::consume), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acquire), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acquire), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::release), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::release), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acq_rel), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::acq_rel), destination);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        // Success because destination == expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::seq_cst), expected);
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_EQ(Atomics::compare_and_swap(destination, expected, value, Atomics::EMemoryOrder::seq_cst), destination);
        ASSERT_EQ(destination, value);
    });
}

TEST(Atomics, compare_and_set_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{};
        T expected = T{};
        alignas(sizeof(T)) T destination = destination_default_value;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = T{};

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(destination, value);
    });
}

TEST(Atomics, compare_and_set_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        T* expected = nullptr;
        T* destination = destination_default_value;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(destination, value);
        destination = destination_default_value;
        expected = nullptr;

        // Success because destination == expected
        ASSERT_TRUE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(destination, value);
        // Failed because destination != expected
        ASSERT_FALSE(Atomics::compare_and_set(destination, expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(destination, value);
    });
}

TEST(Atomics, exchange_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{};
        alignas(sizeof(T)) T destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, value);
    });
}

TEST(Atomics, exchange_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        T* destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::exchange(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, value);
    });
}

TEST(Atomics, fetch_add_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{16};
        alignas(sizeof(T)) T destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
    });
}

TEST(Atomics, fetch_add_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const isize value = 32;
        constexpr T* const  destination_default_value = nullptr;
        T* destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_add(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, destination_default_value + value);
    });
}

TEST(Atomics, fetch_sub_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{ 16 };
        alignas(sizeof(T)) T destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, static_cast<T>(destination_default_value - value));
    });
}

TEST(Atomics, fetch_sub_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const isize value = 32;
        constexpr T* const  destination_default_value = nullptr;
        T* destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
        destination = destination_default_value;

        ASSERT_EQ(Atomics::fetch_sub(destination, value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(destination, destination_default_value - value);
    });
}

TEST(Atomic, default_constructor_of_integral_do_not_initialize_atomic)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        alignas(sizeof(T)) u8 a[sizeof(Atomic<T>)];
        Memory::set(a, u8_max);

        Atomic<T>* atomic = new (a) Atomic<T>;
        ASSERT_NE(atomic->load(), T{});
    });
}

TEST(Atomic, default_constructor_of_pointer_do_not_initialize_atomic)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        alignas(T*) u8 a[sizeof(Atomic<T*>)];
        Memory::set(a, u8_max);

        Atomic<T*>* atomic = new (a) Atomic<T*>;
        ASSERT_NE(atomic->load(), nullptr);
    });
}

TEST(Atomic, constructor_of_integral_initialize_atomic_to_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T> a(32);
        ASSERT_EQ(a.load(), T{ 32 });
    });
}

TEST(Atomic, constructor_of_pointer_with_tag_initialize_atomic_to_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T*> a(reinterpret_cast<T*>(0x32));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(0x32));
    });
}

TEST(Atomic, cast_to_type_load_and_return_the_integral_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T> a(32);
        ASSERT_EQ(static_cast<T>(a), T{ 32 });
    });
}

TEST(Atomic, cast_to_type_load_and_return_the_pointer_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T*> a(reinterpret_cast<T*>(0x32));
        ASSERT_EQ(static_cast<T*>(a), reinterpret_cast<T*>(0x32));
    });
}

TEST(Atomic, volatile_cast_to_type_load_and_return_the_integral_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        volatile Atomic<T> a(32);
        ASSERT_EQ(static_cast<T>(a), T{ 32 });
    });
}

TEST(Atomic, volatile_cast_to_type_load_and_return_the_pointer_value)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        volatile Atomic<T*> a(reinterpret_cast<T*>(0x32));
        ASSERT_EQ(static_cast<T*>(a), reinterpret_cast<T*>(0x32));
    });
}

TEST(Atomic, assign_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T> a(0);
        ASSERT_EQ(a.load(), T{ 0 });
        a = 32;
        ASSERT_EQ(a.load(), T{ 32 });
    });
}

TEST(Atomic, assign_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        Atomic<T*> a(nullptr);
        ASSERT_EQ(a.load(), nullptr);
        a = reinterpret_cast<T*>(0x32);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(0x32));
    });
}

TEST(Atomic, volatile_assign_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        volatile Atomic<T> a(0);
        ASSERT_EQ(a.load(), T{ 0 });
        a = 32;
        ASSERT_EQ(a.load(), T{ 32 });
    });
}

TEST(Atomic, volatile_assign_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        volatile Atomic<T*> a(nullptr);
        ASSERT_EQ(a.load(), nullptr);
        a = reinterpret_cast<T*>(0x32);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(0x32));
    });
}


TEST(Atomic, store_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 0 };

        Atomic<T> a(default_value);

        // Be sure we really test different value
        ASSERT_EQ(a.load(), default_value);

        a.store(value);
        ASSERT_EQ(a.load(), value);
        a.store(default_value);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), default_value);
    });
}

TEST(Atomic, store_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const value = reinterpret_cast<T*>( 0x32);
        T* const default_value = nullptr;

        Atomic<T*> a(default_value);

        // Be sure we really test different value
        ASSERT_EQ(a.load(), default_value);

        a.store(value);
        ASSERT_EQ(a.load(), value);
        a.store(default_value);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), default_value);
    });
}

TEST(Atomic, volatile_store_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 0 };

        volatile Atomic<T> a(default_value);

        // Be sure we really test different value
        ASSERT_EQ(a.load(), default_value);

        a.store(value);
        ASSERT_EQ(a.load(), value);
        a.store(default_value);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), default_value);
    });
}

TEST(Atomic, volatile_store_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const value = reinterpret_cast<T*>(0x32);
        T* const default_value = nullptr;

        volatile Atomic<T*> a(default_value);

        // Be sure we really test different value
        ASSERT_EQ(a.load(), default_value);

        a.store(value);
        ASSERT_EQ(a.load(), value);
        a.store(default_value);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::relaxed);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::release);
        ASSERT_EQ(a.load(), default_value);

        a.store(value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), value);
        a.store(default_value, Atomics::EMemoryOrder::seq_cst);
        ASSERT_EQ(a.load(), default_value);
    });
}

TEST(Atomic, load_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        Atomic<T> a(T{ 32 });

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(a.load(), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::relaxed), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::consume), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::acquire), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::seq_cst), T{ 32 });
    });
}

TEST(Atomic, load_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        Atomic<T*> a(reinterpret_cast<T*>(0x32323232));

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(0x32323232));
    });
}

TEST(Atomic, volatile_load_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        volatile Atomic<T> a(T{ 32 });

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(a.load(), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::relaxed), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::consume), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::acquire), T{ 32 });
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::seq_cst), T{ 32 });
    });
}

TEST(Atomic, volatile_load_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {

        volatile Atomic<T*> a(reinterpret_cast<T*>(0x32323232));

        // Atomics::EMemoryOrder::release and Atomics::EMemoryOrder::acq_rel are not valid memory order for load
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(0x32323232));
        ASSERT_EQ(a.load(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(0x32323232));
    });
}


TEST(Atomic, exchange_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{};
        Atomic<T> a (destination_default_value);

        ASSERT_EQ(a.exchange(value), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(a.load(), value);
    });
}

TEST(Atomic, exchange_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        Atomic<T*> a(destination_default_value);

        ASSERT_EQ(a.exchange(value), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(a.load(), value);
    });
}

TEST(Atomic, volatile_exchange_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T destination_default_value = T{};
        volatile Atomic<T> a(destination_default_value);

        ASSERT_EQ(a.exchange(value), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(a.load(), value);
    });
}

TEST(Atomic, volatile_exchange_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        volatile Atomic<T*> a(destination_default_value);

        ASSERT_EQ(a.exchange(value), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::relaxed), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::consume), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acquire), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::release), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::acq_rel), destination_default_value);
        ASSERT_EQ(a.load(), value);
        a = destination_default_value;

        ASSERT_EQ(a.exchange(value, Atomics::EMemoryOrder::seq_cst), destination_default_value);
        ASSERT_EQ(a.load(), value);
    });
}

TEST(Atomic, compare_exchange_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        T destination_default_value = T{};
        Atomic<T> a(destination_default_value);

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
    });
}


TEST(Atomic, compare_exchange_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        T* expected = nullptr;
        Atomic<T*> a(destination_default_value);

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
    });
}

TEST(Atomic, volatile_compare_exchange_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        T destination_default_value = T{};
        volatile Atomic<T> a(destination_default_value);

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
        destination_default_value = T{};
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(destination_default_value, T{});
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(destination_default_value, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(destination_default_value, value);
    });
}


TEST(Atomic, volatile_compare_exchange_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        T* const  value = reinterpret_cast<T*>(0x32323232);
        constexpr T* const  destination_default_value = nullptr;
        T* expected = nullptr;
        volatile Atomic<T*> a(destination_default_value);

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::relaxed));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::consume));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acquire));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::release));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::acq_rel));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
        expected = destination_default_value;
        a = destination_default_value;

        // Success because a == destination_default_value
        ASSERT_TRUE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange success, the expected value should not be modified
        ASSERT_EQ(expected, nullptr);
        // Failed because a != destination_default_value
        ASSERT_FALSE(a.compare_exchange(expected, value, Atomics::EMemoryOrder::seq_cst));
        ASSERT_EQ(a.load(), value);
        // If exchange failed, the expected value should be set to the atomic stored value
        ASSERT_EQ(expected, value);
    });
}

TEST(Atomic, add_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.add(value), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::relaxed), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::consume), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acquire), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::release), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acq_rel), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::seq_cst), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, volatile_add_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.add(value), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::relaxed), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::consume), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acquire), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::release), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acq_rel), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::seq_cst), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, fetch_add_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_add(value), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, volatile_fetch_add_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_add(value), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, subtract_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.subtract(value), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::relaxed), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::consume), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acquire), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::release), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acq_rel), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::seq_cst), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
    });
}

TEST(Atomic, volatile_subtract_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.subtract(value), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::relaxed), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::consume), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acquire), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::release), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acq_rel), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::seq_cst), static_cast<T>(default_value - value));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
    });
}

TEST(Atomic, fetch_sub_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_sub(value), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
    });
}

TEST(Atomic, volatile_fetch_sub_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T value = T{ 32 };
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_sub(value), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - value));
    });
}

TEST(Atomic, increment_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.increment(), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::relaxed), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::consume), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acquire), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::release), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acq_rel), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::seq_cst), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, volatile_increment_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.increment(), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::relaxed), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::consume), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acquire), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::release), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acq_rel), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::seq_cst), default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, fetch_increment_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_increment(), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, volatile_fetch_increment_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_increment(), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, decrement_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.decrement(), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::relaxed), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::consume), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acquire), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::release), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acq_rel), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::seq_cst), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, volatile_decrement_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.decrement(), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::relaxed), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::consume), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acquire), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::release), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acq_rel), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::seq_cst), static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, fetch_decrement_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_decrement(), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, volatile_fetch_decrement_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a.fetch_decrement(), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, pre_increment_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(++a, default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, volatile_pre_increment_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(++a, default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}


TEST(Atomic, post_increment_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a++, default_value);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, volatile_post_increment_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a++, default_value);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, pre_decrement_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(--a, static_cast<T>(default_value -1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, volatile_pre_decrement_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(--a, static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, post_decrement_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a--, default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, volatile_post_decrement_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a--, default_value);
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, increment_equal_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a+=1, default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, volatile_increment_equal_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a+=1, default_value + 1);
        ASSERT_EQ(a.load(), default_value + 1);
    });
}

TEST(Atomic, decrement_equal_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        Atomic<T> a(default_value);

        ASSERT_EQ(a-=1, static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}

TEST(Atomic, volatile_decrement_equal_operator_integral)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr const T default_value = T{ 16 };
        volatile Atomic<T> a(default_value);

        ASSERT_EQ(a-=1, static_cast<T>(default_value - 1));
        ASSERT_EQ(a.load(), static_cast<T>(default_value - 1));
    });
}


TEST(Atomic, add_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.add(value), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::relaxed), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::consume), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acquire), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::release), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acq_rel), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::seq_cst), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, volatile_add_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T*const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.add(value), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::relaxed), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::consume), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acquire), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::release), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::acq_rel), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.add(value, Atomics::EMemoryOrder::seq_cst), default_value + value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, fetch_add_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_add(value), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}

TEST(Atomic, volatile_fetch_add_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T*const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_add(value), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), default_value + value);
        a = default_value;

        ASSERT_EQ(a.fetch_add(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), default_value + value);
    });
}


TEST(Atomic, subtract_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.subtract(value), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
    });
}

TEST(Atomic, volatile_subtract_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T*const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.subtract(value), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.subtract(value, Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value - value));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
    });
}

TEST(Atomic, fetch_sub_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_sub(value), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
    });
}


TEST(Atomic, volatile_fetch_sub_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        const isize value = 32;
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_sub(value), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
        a = default_value;

        ASSERT_EQ(a.fetch_sub(value, Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - value));
    });
}

TEST(Atomic, increment_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.increment(), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, volatile_increment_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T*const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.increment(), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.increment(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, fetch_increment_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_increment(), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, volatile_fetch_increment_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_increment(), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
        a = default_value;

        ASSERT_EQ(a.fetch_increment(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, decrement_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.decrement(), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, volatile_decrement_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.decrement(), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::relaxed), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::consume), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acquire), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::release), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::acq_rel), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.decrement(Atomics::EMemoryOrder::seq_cst), reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, fetch_decrement_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_decrement(), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, volatile_fetch_decrement_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a.fetch_decrement(), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::relaxed), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::consume), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acquire), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::release), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::acq_rel), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
        a = default_value;

        ASSERT_EQ(a.fetch_decrement(Atomics::EMemoryOrder::seq_cst), default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, pre_increment_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(++a, reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, volatile_pre_increment_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(++a, reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, post_increment_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a++, default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, volatile_post_increment_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a++, default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, pre_decrement_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(--a, reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}


TEST(Atomic, volatile_pre_decrement_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(--a, reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, post_decrement_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a--, default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}

TEST(Atomic, volatile_post_decrement_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a--, default_value);
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}


TEST(Atomic, increment_equal_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a += 1, reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, volatile_increment_equal_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T* const default_value = nullptr;
        volatile Atomic<T*> a(default_value);

        ASSERT_EQ(a += 1, reinterpret_cast<T*>(default_value + 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value + 1));
    });
}

TEST(Atomic, decrement_equal_operator_pointer)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, u8, i16, u16, i32, u32, i64, u64, usize, isize>()([]<typename T>() {
        constexpr T*const default_value = nullptr;
        Atomic<T*> a(default_value);

        ASSERT_EQ(a -= 1, reinterpret_cast<T*>(default_value - 1));
        ASSERT_EQ(a.load(), reinterpret_cast<T*>(default_value - 1));
    });
}