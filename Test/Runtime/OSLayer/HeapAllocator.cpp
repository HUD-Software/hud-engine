#include <OSLayer/Allocators/HeapAllocator.h>


TEST(HeapAllocator, allocate_zero_do_not_allocate)
{
    using namespace hud;
    HUD_TEST::for_each_type<i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, uptr, iptr, usize, isize>()([]<typename T>() {
        hud::HeapAllocator heap_allocator;
        const auto buffer = heap_allocator.template allocate<T>(0);
        ASSERT_EQ(buffer.data(), nullptr);
        ASSERT_EQ(buffer.count(), 0u);
    });
}

TEST(HeapAllocator, correctly_allocate_and_free_requested_amount_of_memory)
{
    using namespace hud;
    HUD_TEST::for_each_type<i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, uptr, iptr, usize, isize>()([]<typename T>() {
        for (u32 count = 1; count < i8_max; count++) {
            hud::HeapAllocator heap_allocator;
            const auto buffer = heap_allocator.template allocate<T>(count);
            ASSERT_NE(buffer.data(), nullptr);
            ASSERT_EQ(buffer.count(), count);
            ASSERT_EQ(buffer.end() - buffer.begin(), isize(count));

            // Write in the allocated memory
            // If memory is not allocated, write access violation should happend
            isize write_index = 0;
            for (T& value : buffer) {
                value = static_cast<T>(write_index);
                write_index++;
            }

            // Ensure we correctly write values of index in the correct memory
            for (usize read_index = 0; read_index < buffer.count(); read_index++) {
                ASSERT_EQ(buffer[read_index], static_cast<T>(read_index));
            }

            heap_allocator.free(buffer);
        }
    });
}