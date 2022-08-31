#include <OSLayer/Containers/AlignedBuffer.h>

TEST(AlignedBuffer, default_constructor_should_aligned_buffer_correctly)
{
    using namespace hud;
    using size = std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8, 9>;
    using align = std::integer_sequence<int, 1, 2, 4, 8, 16, 32, 64, 128>;
    HUD_TEST::for_each_value<size>()([]<int size>() {
        HUD_TEST::for_each_value<align>()([]<int alignement>() {
            AlignedBuffer<size, alignement> buffer;
            ASSERT_TRUE(Memory::is_pointer_aligned(buffer.pointer(), alignement));
        });
    });
}