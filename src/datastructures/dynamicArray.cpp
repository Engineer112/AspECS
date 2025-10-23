//
// Created by Hosea on 10/20/2025.
//

#include "datastructures/dynamicArray.h"


#include <cstdlib>
#include <cstring>

bool DynamicArray_Init(DynamicArray *array, const size_t elementSize, const size_t initialCapacity) {
    array->ElementSize = elementSize;
    array->Size = 0;
    array->Capacity = initialCapacity;
    array->Data = malloc(elementSize * initialCapacity);
    if (array->Data == nullptr) {
        return false;
    }

    return true;
}

bool DynamicArray_PushBack(DynamicArray *array, const void *element) {
    if (array->Size >= array->Capacity) {
        // calculate new capacity accounting for if its 0
        const size_t newCapacity = array->Capacity ? array->Capacity * 2 : 1;
        void* newData = realloc(array->Data, newCapacity * array->ElementSize);

        // check if failure accured
        if (!newData) return false;

        // update array
        array->Data = newData;
        array->Capacity = newCapacity;
    }

    // set and create new element
    if (element != nullptr) {
        void* target = static_cast<char *>(array->Data) + array->Size * array->ElementSize;
        memcpy(target, element, array->ElementSize);
    }
    array->Size++;

    return true;
}

void DynamicArray_PopBack(DynamicArray *array) {
    array->Size--;
}

bool DynamicArray_PopBack(DynamicArray *array, void *outElement) {
    // is it empty?
    if (array->Size == 0) return false;

    const size_t lastElementIndex = array->Size - 1;
    const void *lastElementPtr = DynamicArray_Get(array, lastElementIndex);

    // let the caller know the value of the element that was removed
    if (outElement)
        memcpy(outElement, lastElementPtr, array->ElementSize);

    // remove element
    DynamicArray_PopBack(array);
    return true;
}

void *DynamicArray_Get(const DynamicArray *array, const size_t index) {
    // is it empty?
    if (index >= array->Size) return nullptr;

    // return a pointer to the requested element
    return static_cast<char *>(array->Data) + index * array->ElementSize;
}

bool DynamicArray_Set(const DynamicArray *array, const size_t index, const void *element) {
    // is it empty?
    if (index >= array->Size) return false;

    void* targetElementPtr = static_cast<char *>(array->Data) + index * array->ElementSize;

    // set the elements value
    memcpy(targetElementPtr, element, array->ElementSize);
    return true;
}

void DynamicArray_Free(DynamicArray* array) {
    free(array->Data);
    array->Data = nullptr;
    array->Size = array->Capacity = array->ElementSize = 0;
}

bool DynamicArray_Resize(DynamicArray *array, const size_t newCapacity) {
    if (newCapacity < array->Size) array->Size = newCapacity;
    void* newData = realloc(array->Data, newCapacity * array->ElementSize);

    // did it allocate okay?
    if (!newData) return false;

    array->Data = newData;
    array->Capacity = newCapacity;

    return true;
}

bool DynamicArray_Reserve(DynamicArray* array, const size_t minCapacity) {
    // only allocate more if we don't already have it
    if (minCapacity > array->Capacity) {
        void* newData = realloc(array->Data, minCapacity * array->ElementSize);

        if (!newData) return false;
        array->Data = newData;
        array->Capacity = minCapacity;
    }

    return true;
}