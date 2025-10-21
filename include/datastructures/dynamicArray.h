//
// Created by Hosea on 10/20/2025.
//

#pragma once

#include <cstdlib>

typedef struct {
    void* Data;            // Pointer to raw memory
    size_t ElementSize;    // Size of each element
    size_t Size;           // Number of elements
    size_t Capacity;       // Allocated capacity
} DynamicArray;

void DynamicArray_Init(DynamicArray* array, size_t elementSize, size_t initialCapacity);
void DynamicArray_PushBack(DynamicArray* array, const void* element);
void* DynamicArray_PopBack(DynamicArray* array);
void* DynamicArray_Get(const DynamicArray* array, size_t index);
void DynamicArray_Free(DynamicArray* array);
void DynamicArray_Resize(DynamicArray* array, size_t newCapacity);
void DynamicArray_Reserve(DynamicArray* array, size_t minCapacity);