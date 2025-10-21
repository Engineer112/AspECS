//
// Created by Hosea on 10/21/2025.
//

#pragma once
#include "dynamicArray.h"

struct resourcePool {
    DynamicArray Resources;
    DynamicArray FreeIndices;
};

inline void ResourcePool_Init(resourcePool& pool, const size_t elementSize, const size_t initialCapacity) {
    DynamicArray_Init(&pool.Resources, elementSize, initialCapacity);
    DynamicArray_Init(&pool.FreeIndices, sizeof(size_t), 0);
}

inline void ResourcePool_Destroy(resourcePool& pool) {
    DynamicArray_Free(&pool.Resources);
    DynamicArray_Free(&pool.FreeIndices);
}

inline void* ResourcePool_Get(const resourcePool& pool, const size_t index) {
    return DynamicArray_Get(&pool.Resources, index);
}

inline size_t ResourcePool_GetAvailableSlot(resourcePool& pool) {
    const size_t* slotPtr = static_cast<size_t*>(DynamicArray_PopBack(&pool.FreeIndices));
    if (slotPtr) {
        return *slotPtr;
    }
    return pool.Resources.Size; // next free index
}

inline void ResourcePool_ReleaseSlot(resourcePool& pool, const size_t index) {
    DynamicArray_PushBack(&pool.FreeIndices, &index);
}
