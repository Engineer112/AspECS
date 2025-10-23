//
// Created by Hosea on 10/21/2025.
//

#include <gtest/gtest.h>
#include "datastructures/dynamicArray.h"

// ---------- Utility ----------
static void PushInts(DynamicArray* array, std::initializer_list<int> values) {
    for (int v : values)
        DynamicArray_PushBack(array, &v);
}

// ---------- Tests ----------

TEST(DynamicArrayTests, InitSetsFieldsCorrectly) {
    // Arrange
    DynamicArray array{};

    // Act
    DynamicArray_Init(&array, sizeof(int), 4);

    // Assert
    EXPECT_EQ(array.ElementSize, sizeof(int));
    EXPECT_EQ(array.Size, 0);
    EXPECT_EQ(array.Capacity, 4);
    EXPECT_NE(array.Data, nullptr);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, FreeResetsAllFieldsToZero) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 3);
    int val = 1;
    DynamicArray_PushBack(&array, &val);

    // Act
    DynamicArray_Free(&array);

    // Assert
    EXPECT_EQ(array.Data, nullptr);
    EXPECT_EQ(array.Size, 0);
    EXPECT_EQ(array.Capacity, 0);
    EXPECT_EQ(array.ElementSize, 0);
}

TEST(DynamicArrayTests, PushBackAddsElementsAndGrowsWhenNeeded) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);
    int a = 10, b = 20, c = 30;

    // Act
    DynamicArray_PushBack(&array, &a);
    DynamicArray_PushBack(&array, &b);
    DynamicArray_PushBack(&array, &c); // triggers realloc

    // Assert
    EXPECT_EQ(array.Size, 3);
    EXPECT_GE(array.Capacity, 3);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 0)), 10);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 20);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 2)), 30);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, GetReturnsNullWhenIndexOutOfBounds) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 1);
    int val = 42;
    DynamicArray_PushBack(&array, &val);

    // Act & Assert
    EXPECT_NE(DynamicArray_Get(&array, 0), nullptr);
    EXPECT_EQ(DynamicArray_Get(&array, 1), nullptr);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, ResizeReducesSizeAndKeepsDataIntact) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 5);
    PushInts(&array, {1, 2, 3, 4, 5});

    // Act
    DynamicArray_Resize(&array, 3);

    // Assert
    EXPECT_EQ(array.Size, 3);
    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, i)), i + 1);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, ReserveIncreasesCapacityButNotSize) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);

    // Act
    DynamicArray_Reserve(&array, 10);

    // Assert
    EXPECT_EQ(array.Size, 0);
    EXPECT_GE(array.Capacity, 10);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, PopBackReturnsLastElementAndDecrementsSize) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 3);
    PushInts(&array, {5, 10, 15});
    int value = 0;

    // Act
    bool popped = DynamicArray_PopBack(&array, &value);

    // Assert
    EXPECT_TRUE(popped);
    EXPECT_EQ(value, 15);
    EXPECT_EQ(array.Size, 2);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, PopBackOnEmptyArrayReturnsFalse) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);
    int temp = -1;

    // Act
    bool popped = DynamicArray_PopBack(&array, &temp);

    // Assert
    EXPECT_FALSE(popped);
    EXPECT_EQ(temp, -1);
    EXPECT_EQ(array.Size, 0);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, PushAfterPopBackReusesSpaceCorrectly) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);
    PushInts(&array, {1, 2});
    int temp;
    DynamicArray_PopBack(&array, &temp);
    int val3 = 3;

    // Act
    DynamicArray_PushBack(&array, &val3);

    // Assert
    EXPECT_EQ(array.Size, 2);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 3);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, ReallocPreservesExistingData) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);
    PushInts(&array, {10, 20});
    int extra = 30;

    // Act
    DynamicArray_PushBack(&array, &extra); // triggers realloc

    // Assert
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 0)), 10);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 20);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 2)), 30);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, SetReplacesExistingElementValue) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 3);
    PushInts(&array, {1, 2, 3});
    int newVal = 99;

    // Act
    bool success = DynamicArray_Set(&array, 1, &newVal);

    // Assert
    EXPECT_TRUE(success);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 99);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTests, SetFailsForInvalidIndex) {
    // Arrange
    DynamicArray array{};
    DynamicArray_Init(&array, sizeof(int), 2);
    PushInts(&array, {5});
    int newVal = 42;

    // Act
    bool success = DynamicArray_Set(&array, 5, &newVal);

    // Assert
    EXPECT_FALSE(success);

    DynamicArray_Free(&array);
}
