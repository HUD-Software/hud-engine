#include <OSLayer/Allocators/AlignedHeapAllocator.h>

TEST(AlignedHeapAllocator, allocate_zero_do_not_allocate)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, uptr, iptr, usize, isize>()([]<typename T>() {
        hud::AlignedHeapAllocator<alignof(T)> heap_allocator;
        const auto buffer = heap_allocator.template allocate<T>(0);
        ASSERT_EQ(buffer.data(), nullptr);
        ASSERT_EQ(buffer.count(), 0u);
    });
}

struct ForType
{
    template<typename T>
    void operator()() {
        using namespace hud;
        HUD_TEST::for_each_value<u32, 1, 2, 4, 8, 16, 32, 64, 128, 256, 1024>()([]<u32 alignement>() {
            for (u32 count = 1; count < i8_max; count++) {
                hud::AlignedHeapAllocator<alignement> heap_allocator;
                const auto buffer = heap_allocator.template allocate<T>(count);
                ASSERT_NE(buffer.data(), nullptr);
                ASSERT_EQ(buffer.count(), count);
                ASSERT_EQ(buffer.end() - buffer.begin(), iptr(count));
                ASSERT_TRUE(hud::Memory::is_pointer_aligned(buffer.data(), alignement));

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
                ASSERT_EQ(buffer.data(), nullptr);
                ASSERT_EQ(buffer.count(), 0u);
                ASSERT_EQ(buffer.end() - buffer.begin(), 0);
            }
        });
    }
};

TEST(AlignedHeapAllocator, correctly_allocate_and_free_aligned_requested_amount_of_memory)
{
    using namespace hud;

    HUD_TEST::for_each_type<i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, uptr, iptr, usize, isize>()([]<typename T>() {
        HUD_TEST::for_each_value<u32, 1, 2, 4, 8, 16, 32, 64, 128, 256, 1024>()([]<u32 alignement>() {
            for (u32 count = 1; count < i8_max; count++) {
                hud::AlignedHeapAllocator<alignement> heap_allocator;
                const auto buffer = heap_allocator.template allocate<T>(count);
                ASSERT_NE(buffer.data(), nullptr);
                ASSERT_EQ(buffer.count(), count);
                ASSERT_EQ(buffer.end() - buffer.begin(), static_cast<iptr>(count));
                ASSERT_TRUE(hud::Memory::is_pointer_aligned(buffer.data(), alignement));

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
    });
}