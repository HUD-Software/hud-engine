#include <OSLayer/Containers/Array.h>
#include "Allocators.h"

TEST(Array, find_first_index_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_first_index(10), index_none);

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_EQ(array.find_first_index(10), 0u);
    ASSERT_EQ(array.find_first_index(20), 1u);
    ASSERT_EQ(array.find_first_index(30), 2u);
    ASSERT_EQ(array.find_first_index(40), 3u);
    ASSERT_EQ(array.find_first_index(50), 4u);
    ASSERT_EQ(array.find_first_index(0), index_none);
}

TEST(Array, find_first_index_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_first_index(10u), index_none);

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_EQ(array.find_first_index(10u), 0u);
    ASSERT_EQ(array.find_first_index(20u), 1u);
    ASSERT_EQ(array.find_first_index(30u), 2u);
    ASSERT_EQ(array.find_first_index(40u), 3u);
    ASSERT_EQ(array.find_first_index(50u), 4u);
    ASSERT_EQ(array.find_first_index(0u), index_none);
}

TEST(Array, find_last_index_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_last_index(10), index_none);

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_EQ(array.find_last_index(10), 5u);
    ASSERT_EQ(array.find_last_index(20), 6u);
    ASSERT_EQ(array.find_last_index(30), 7u);
    ASSERT_EQ(array.find_last_index(40), 8u);
    ASSERT_EQ(array.find_last_index(50), 9u);
    ASSERT_EQ(array.find_last_index(0), index_none);
}

TEST(Array, find_last_index_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_last_index(10u), index_none);

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_EQ(array.find_last_index(10u), 5u);
    ASSERT_EQ(array.find_last_index(20u), 6u);
    ASSERT_EQ(array.find_last_index(30u), 7u);
    ASSERT_EQ(array.find_last_index(40u), 8u);
    ASSERT_EQ(array.find_last_index(50u), 9u);
    ASSERT_EQ(array.find_last_index(0u), index_none);
}

TEST(Array, find_first_index_by_predicate_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 10; }), index_none);

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 10; }), 0u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 20; }), 1u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 30; }), 2u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 40; }), 3u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 50; }), 4u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element.id() == 0; }), index_none);
}

TEST(Array, find_first_index_by_predicate_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 10u; }), index_none);

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 10u; }), 0u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 20u; }), 1u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 30u; }), 2u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 40u; }), 3u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 50u; }), 4u);
    ASSERT_EQ(array.find_first_index_by_predicate([](const Type& element) { return element == 0u; }), index_none);
}

TEST(Array, find_last_index_by_predicate_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 10; }), index_none);

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 10; }), 5u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 20; }), 6u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 30; }), 7u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 40; }), 8u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 50; }), 9u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element.id() == 0; }), index_none);
}

TEST(Array, find_last_index_by_predicate_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 10u; }), index_none);

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 10u; }), 5u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 20u; }), 6u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 30u; }), 7u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 40u; }), 8u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 50u; }), 9u);
    ASSERT_EQ(array.find_last_index_by_predicate([](const Type& element) { return element == 0u; }), index_none);
}

TEST(Array, contains_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_FALSE(array.contains(10));

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_TRUE(array.contains(10));
    ASSERT_TRUE(array.contains(20));
    ASSERT_TRUE(array.contains(30));
    ASSERT_TRUE(array.contains(40));
    ASSERT_TRUE(array.contains(50));
    ASSERT_FALSE(array.contains(0));
}

TEST(Array, contains_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_FALSE(array.contains(10u));

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_TRUE(array.contains(10u));
    ASSERT_TRUE(array.contains(20u));
    ASSERT_TRUE(array.contains(30u));
    ASSERT_TRUE(array.contains(40u));
    ASSERT_TRUE(array.contains(50u));
    ASSERT_FALSE(array.contains(0u));
}

TEST(Array, contains_by_predicate_non_trivial_type)
{
    using namespace hud;
    using Type = HUD_TEST::NonBitwiseType;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_FALSE(array.contains_by_predicate([](const Type& element) { return element.id() == 10; }));

    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);
    array.emplace_back(10, nullptr);
    array.emplace_back(20, nullptr);
    array.emplace_back(30, nullptr);
    array.emplace_back(40, nullptr);
    array.emplace_back(50, nullptr);

    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element.id() == 10; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element.id() == 20; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element.id() == 30; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element.id() == 40; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element.id() == 50; }));
    ASSERT_FALSE(array.contains_by_predicate([](const Type& element) {return element.id() == 0; }));
}

TEST(Array, contains_by_predicate_trivial_type)
{
    using namespace hud;
    using Type = usize;
    using ArrayType = Array<Type, HUD_TEST::ArrayAllocator<alignof(Type)>>;

    ArrayType array;

    // Empty find return nothing
    ASSERT_FALSE(array.contains_by_predicate([](const Type& element) { return element == 10u; }));

    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);
    array.emplace_back(10);
    array.emplace_back(20);
    array.emplace_back(30);
    array.emplace_back(40);
    array.emplace_back(50);

    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element == 10u; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element == 20u; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element == 30u; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element == 40u; }));
    ASSERT_TRUE(array.contains_by_predicate([](const Type& element) {return element == 50u; }));
    ASSERT_FALSE(array.contains_by_predicate([](const Type& element) {return element == 0u; }));
}