#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

TEST(Array, emplace_back_to_ref_can_default_construct_non_trivially_default_constructible_type)
{
    using namespace hud;
    using Type = HUD_TEST::DefaultConstructibleType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(!IsTriviallyDefaultConstructibleV<Type>);
    static_assert(IsDefaultConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref();

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index].id(), HUD_TEST::DefaultConstructibleType::DEFAULT_ID_VALUE);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref();

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index].id(), HUD_TEST::DefaultConstructibleType::DEFAULT_ID_VALUE);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_default_construct_trivially_default_constructible_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(IsTriviallyDefaultConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref();

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], 0u);  // default value of usize is 0 when construct

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref();

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], 0u);  // default value of usize is 0 when construct

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_construct_non_trivially_constructible_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonDefaultConstructibleType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(!IsTriviallyConstructibleV<Type, usize>);
    static_assert(IsConstructibleV<Type, usize>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref(static_cast<i32>(index));

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }


    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref(static_cast<i32>(index));

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_construct_trivially_constructible_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(IsTriviallyConstructibleV<Type, usize>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref(static_cast<i32>(index));

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], index);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }


    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace default construct element
            const Type& ref = array.emplace_back_to_ref(static_cast<i32>(index));

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], index);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_copy_construct_non_trivially_copy_constructible_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseCopyConstructibleType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(!IsTriviallyCopyConstructibleV<Type>);
    static_assert(IsCopyConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            const Type element_to_copy(index);
            ASSERT_EQ(element_to_copy.copy_constructor_count(), 0u);

            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(element_to_copy);

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].copy_constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace copy construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            const Type element_to_copy(index);
            ASSERT_EQ(element_to_copy.copy_constructor_count(), 0u);

            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(element_to_copy);

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].copy_constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_copy_construct_trivially_copy_constructible_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(IsTriviallyCopyConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace copy construct element
            const Type element_to_copy(index);
            const Type& ref = array.emplace_back_to_ref(element_to_copy);

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], element_to_copy);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace copy construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace copy construct element
            const Type element_to_copy(index);
            const Type& ref = array.emplace_back_to_ref(element_to_copy);

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], element_to_copy);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_move_construct_non_bitwise_move_constructible_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseMoveConstructibleType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(!IsBitwiseMoveConstructibleV<Type>);
    static_assert(IsMoveConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            Type element_to_move(index);
            ASSERT_EQ(element_to_move.move_constructor_count(), 0u);

            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(hud::move(element_to_move));

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].move_constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace copy construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            Type element_to_move(index);
            ASSERT_EQ(element_to_move.move_constructor_count(), 0u);

            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(hud::move(element_to_move));

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(static_cast<usize>(ref.id()), index);
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(static_cast<usize>(array[index].id()), index);
            ASSERT_EQ(array[index].move_constructor_count(), 1u);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}

TEST(Array, emplace_back_to_ref_can_move_construct_bitwise_move_constructible_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;
    static_assert(IsBitwiseMoveConstructibleV<Type>);

    // test with reallocation
    for (usize element_count = 0; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace default construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(Type(index));

            // Ensure the array grows
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), index + 1);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], index);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), index + 1);
            ASSERT_EQ(array.allocator().free_count(), index);
        }
    }

    // test with no reallocation
    for (usize element_count = 1; element_count < 5; element_count++) {
        ArrayType array;
        ASSERT_EQ(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), 0u);
        ASSERT_EQ(array.allocator().allocation_count(), 0u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        array.reserve(element_count);
        ASSERT_NE(array.data(), nullptr);
        ASSERT_EQ(array.count(), 0u);
        ASSERT_EQ(array.max_count(), element_count);
        ASSERT_EQ(array.allocator().allocation_count(), 1u);
        ASSERT_EQ(array.allocator().free_count(), 0u);

        // Emplace copy construct a list of elements
        for (usize index = 0; index < element_count; index++) {
            // Emplace copy construct element
            const Type& ref = array.emplace_back_to_ref(Type(index));

            // Ensure the array has not grown
            ASSERT_NE(array.data(), nullptr);
            ASSERT_EQ(array.count(), index + 1);
            ASSERT_EQ(array.max_count(), element_count);

            // Ensure the returned ref is refering to the correct element
            ASSERT_EQ(&ref, &array[index]);
            ASSERT_EQ(array[index], index);

            // Ensure we really reallocate
            ASSERT_EQ(array.allocator().allocation_count(), 1u);
            ASSERT_EQ(array.allocator().free_count(), 0u);
        }
    }
}