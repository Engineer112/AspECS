//
// Created by Hosea on 10/20/2025.
//

#pragma once

#include <cstdlib>

typedef struct {
    void* Data;            // Pointer to raw memory array
    size_t ElementSize;    // Size of each element
    size_t Size;           // Number of elements
    size_t Capacity;       // Allocated capacity (bytes)
} DynamicArray;

bool DynamicArray_Init(DynamicArray *array, size_t elementSize, size_t initialCapacity);

bool DynamicArray_PushBack(DynamicArray *array, const void *element);

void DynamicArray_PopBack(DynamicArray *array);

bool DynamicArray_PopBack(DynamicArray *array, void *outElement);

void *DynamicArray_Get(const DynamicArray *array, size_t index);

bool DynamicArray_Set(const DynamicArray *array, size_t index, const void *element);
void DynamicArray_Free(DynamicArray* array);

bool DynamicArray_Resize(DynamicArray *array, size_t newCapacity);
bool DynamicArray_Reserve(DynamicArray* array, size_t minCapacity);
