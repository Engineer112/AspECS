//
// Created by Hosea on 10/20/2025.
//

#include "datastructures/dynamicArray.h"


#include <cstdlib>
#include <cstring>

void DynamicArray_Init(DynamicArray* array, const size_t elementSize, const size_t initialCapacity) {
    array->ElementSize = elementSize;
    array->Size = 0;
    array->Capacity = initialCapacity;
    array->Data = malloc(elementSize * initialCapacity);
}

void DynamicArray_PushBack(DynamicArray* array, const void* element) {
    if (array->Size >= array->Capacity) {
        const size_t newCapacity = array->Capacity ? array->Capacity * 2 : 1;
        void* newData = realloc(array->Data, newCapacity * array->ElementSize);
        if (!newData) return; // fail silently or log
        array->Data = newData;
        array->Capacity = newCapacity;
    }

    void* target = static_cast<char *>(array->Data) + array->Size * array->ElementSize;
    memcpy(target, element, array->ElementSize);
    array->Size++;
}

void* DynamicArray_PopBack(DynamicArray* array) {
    if (array->Size == 0) return nullptr;

    const size_t lastIndex = array->Size - 1;
    void* element = DynamicArray_Get(array, lastIndex);
    array->Size--;

    return element;
}

void* DynamicArray_Get(const DynamicArray* array, const size_t index) {
    if (index >= array->Size) return nullptr;
    return static_cast<char *>(array->Data) + index * array->ElementSize;
}

void DynamicArray_Free(DynamicArray* array) {
    free(array->Data);
    array->Data = nullptr;
    array->Size = array->Capacity = array->ElementSize = 0;
}

void DynamicArray_Resize(DynamicArray* array, const size_t newCapacity) {
    if (newCapacity < array->Size) array->Size = newCapacity;
    void* newData = realloc(array->Data, newCapacity * array->ElementSize);
    if (!newData && newCapacity > 0) return;
    array->Data = newData;
    array->Capacity = newCapacity;
}

void DynamicArray_Reserve(DynamicArray* array, const size_t minCapacity) {
    if (minCapacity > array->Capacity) {
        void* newData = realloc(array->Data, minCapacity * array->ElementSize);
        if (!newData) return;
        array->Data = newData;
        array->Capacity = minCapacity;
    }
}