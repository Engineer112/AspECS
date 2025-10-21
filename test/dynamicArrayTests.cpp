//
// Created by Hosea on 10/21/2025.
//

#include <gtest/gtest.h>
#include "datastructures/dynamicArray.h"

TEST(DynamicArrayTest, InitSetsFieldsCorrectly) {
    // Arrange
    DynamicArray array;

    // Act
    DynamicArray_Init(&array, sizeof(int), 4);

    // Assert
    EXPECT_EQ(array.ElementSize, sizeof(int));
    EXPECT_EQ(array.Size, 0);
    EXPECT_EQ(array.Capacity, 4);
    EXPECT_NE(array.Data, nullptr);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, PushBackStoresAndGrows) {
    // Arrange
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 2);
    int a = 10, b = 20, c = 30;

    // Act
    DynamicArray_PushBack(&array, &a);
    DynamicArray_PushBack(&array, &b);
    DynamicArray_PushBack(&array, &c); // triggers realloc

    // Assert
    EXPECT_EQ(array.Size, 3);
    EXPECT_GE(array.Capacity, 3);

    EXPECT_EQ(*static_cast<int *>(DynamicArray_Get(&array, 0)), 10);
    EXPECT_EQ(*static_cast<int *>(DynamicArray_Get(&array, 1)), 20);
    EXPECT_EQ(*static_cast<int *>(DynamicArray_Get(&array, 2)), 30);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, GetReturnsNullOutOfBounds) {
    // Arrange
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 1);
    int val = 42;
    DynamicArray_PushBack(&array, &val);

    // Act & Assert
    EXPECT_NE(DynamicArray_Get(&array, 0), nullptr);
    EXPECT_EQ(DynamicArray_Get(&array, 1), nullptr);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, ResizeShrinksSizeAndPreservesData) {
    // Arrange
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 5);
    int val = 99;
    for (int i = 0; i < 5; ++i) DynamicArray_PushBack(&array, &val);

    // Act
    DynamicArray_Resize(&array, 3);

    // Assert
    EXPECT_EQ(array.Size, 3);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(*static_cast<int *>(DynamicArray_Get(&array, i)), 99);
    }

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, ReserveIncreasesCapacityOnly) {
    // Arrange
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 2);

    // Act
    DynamicArray_Reserve(&array, 10);

    // Assert
    EXPECT_EQ(array.Size, 0);
    EXPECT_GE(array.Capacity, 10);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, FreeResetsFields) {
    // Arrange
    DynamicArray array;
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

TEST(DynamicArray, PopBackRemovesLastElementAndResizesArray) {
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 3);

    int value = 0;
    DynamicArray_PushBack(&array, &value);

    void* temp = DynamicArray_PopBack(&array);
    ASSERT_NE(temp, nullptr);  // Ensure pop didn't return null
    EXPECT_EQ(*static_cast<int*>(temp), 0);
}

TEST(DynamicArrayTest, PopBackReturnsNullWhenEmpty) {
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 2);

    void* result = DynamicArray_PopBack(&array);
    EXPECT_EQ(result, nullptr);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, PushAfterPopBackWorks) {
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 2);

    int val1 = 1, val2 = 2;
    DynamicArray_PushBack(&array, &val1);
    DynamicArray_PushBack(&array, &val2);
    DynamicArray_PopBack(&array);

    int val3 = 3;
    DynamicArray_PushBack(&array, &val3);

    EXPECT_EQ(array.Size, 2);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 3);

    DynamicArray_Free(&array);
}

TEST(DynamicArrayTest, ReallocPreservesOldElements) {
    DynamicArray array;
    DynamicArray_Init(&array, sizeof(int), 2);

    int values[] = {10, 20};
    DynamicArray_PushBack(&array, &values[0]);
    DynamicArray_PushBack(&array, &values[1]);
    int extra = 30;
    DynamicArray_PushBack(&array, &extra); // triggers realloc

    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 0)), 10);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 1)), 20);
    EXPECT_EQ(*static_cast<int*>(DynamicArray_Get(&array, 2)), 30);

    DynamicArray_Free(&array);
}

