//
// Created by Hosea on 10/21/2025.
//
#include "datastructures/resourcePool.h"
#include "gtest/gtest.h"

// --- Helper setup for clarity ---
static resourcePool MakePool(size_t elementSize = sizeof(int), size_t initialCapacity = 4) {
    resourcePool pool{};
    ResourcePool_Init(pool, elementSize, initialCapacity);
    return pool;
}

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

TEST(ResourcePoolTests, InitAndDestroy_CreatesAndFreesMemory) {
    // Arrange
    resourcePool pool = MakePool();

    // Assert initial state
    EXPECT_NE(pool.Resources.Data, nullptr);
    EXPECT_NE(pool.FreeIndices.Data, nullptr);
    EXPECT_EQ(pool.Resources.ElementSize, sizeof(int));
    EXPECT_EQ(pool.Resources.Size, 0);
    EXPECT_EQ(pool.FreeIndices.Size, 0);

    // Act
    ResourcePool_Destroy(pool);

    // Assert cleanup
    EXPECT_EQ(pool.Resources.Data, nullptr);
    EXPECT_EQ(pool.FreeIndices.Data, nullptr);
}

TEST(ResourcePoolTests, Allocateelement_ReturnsSequentialIndices_WhenNoFreeelements) {
    // Arrange
    resourcePool pool = MakePool();

    // Act
    size_t first = ResourcePool_AllocateElement(pool);
    size_t second = ResourcePool_AllocateElement(pool);

    // Assert
    EXPECT_EQ(first, 0);
    EXPECT_EQ(second, 1);
    EXPECT_EQ(pool.FreeIndices.Size, 0);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, Allocateelement_ReusesReleasedIndices) {
    // Arrange
    resourcePool pool = MakePool();
    size_t a = ResourcePool_AllocateElement(pool);
    size_t b = ResourcePool_AllocateElement(pool);
    size_t c = ResourcePool_AllocateElement(pool);

    // Act
    ResourcePool_ReleaseElement(pool, b);
    size_t reused = ResourcePool_AllocateElement(pool);

    // Assert
    EXPECT_EQ(reused, b);
    EXPECT_EQ(pool.FreeIndices.Size, 0);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, AddElement_AppendsNewResource_WhenNoFreeelements) {
    // Arrange
    resourcePool pool = MakePool();
    int value = 42;

    // Act
    size_t element = ResourcePool_AddElement(pool, &value);

    // Assert
    EXPECT_EQ(element, 0);
    EXPECT_EQ(pool.Resources.Size, 1);
    EXPECT_EQ(*(int*)ResourcePool_Get(pool, element), 42);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, AddElement_Reuseselement_WhenReleased) {
    // Arrange
    resourcePool pool = MakePool();
    int a = 11, b = 22, c = 33;

    size_t sa = ResourcePool_AddElement(pool, &a);
    size_t sb = ResourcePool_AddElement(pool, &b);
    ResourcePool_ReleaseElement(pool, sa);

    // Act
    size_t sc = ResourcePool_AddElement(pool, &c);

    // Assert
    EXPECT_EQ(sc, sa);
    EXPECT_EQ(pool.Resources.Size, 2);
    EXPECT_EQ(*static_cast<int *>(ResourcePool_Get(pool, sc)), 33);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, Get_ReturnsCorrectPointer) {
    // Arrange
    resourcePool pool = MakePool( sizeof(int), 2 );
    int a = 7;
    int b = 9;

    size_t ia = ResourcePool_AddElement(pool, &a);
    size_t ib = ResourcePool_AddElement(pool, &b);

    // Act
    int* pa = static_cast<int*>(ResourcePool_Get(pool, ia));
    int* pb = static_cast<int*>(ResourcePool_Get(pool, ib));

    // Assert
    EXPECT_EQ(*pa, 7);
    EXPECT_EQ(*pb, 9);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, Releaseelement_AddsToFreeList) {
    // Arrange
    resourcePool pool = MakePool();
    size_t element = ResourcePool_AllocateElement(pool);

    // Act
    ResourcePool_ReleaseElement(pool, element);

    // Assert
    EXPECT_EQ(pool.FreeIndices.Size, 1);
    size_t releasedIndex =
        *static_cast<size_t *>(DynamicArray_Get(&pool.FreeIndices, pool.FreeIndices.Size - 1));
    EXPECT_EQ(releasedIndex, element);

    ResourcePool_Destroy(pool);
}

TEST(ResourcePoolTests, ReserveElements_ReservesForBothResourcesAndFreeIndices) {
    resourcePool pool = MakePool();

    constexpr int resourceCapacity = 20;
    constexpr int freeIndicesCapacity = 10;
    EXPECT_TRUE(ResourcePool_Reserve(pool, resourceCapacity, freeIndicesCapacity));
    EXPECT_TRUE(pool.Resources.Capacity == resourceCapacity);
    EXPECT_TRUE(pool.FreeIndices.Capacity == freeIndicesCapacity);

    ResourcePool_Destroy(pool);
}