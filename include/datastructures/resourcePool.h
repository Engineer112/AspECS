//
// Created by Hosea on 10/21/2025.
//

#pragma once
#include <cassert>
#include <cstring>

#include "dynamicArray.h"

struct resourcePool {
    DynamicArray Resources;
    DynamicArray FreeIndices;
};

inline void ResourcePool_Init(resourcePool& pool, const size_t elementSize, const size_t initialCapacity) {
    DynamicArray_Init(&pool.Resources, elementSize, initialCapacity);
    DynamicArray_Init(&pool.FreeIndices, sizeof(size_t), initialCapacity / 4);
}

inline void ResourcePool_Destroy(resourcePool& pool) {
    DynamicArray_Free(&pool.Resources);
    DynamicArray_Free(&pool.FreeIndices);
}

inline void* ResourcePool_Get(const resourcePool& pool, const size_t index) {
    return DynamicArray_Get(&pool.Resources, index);
}

size_t ResourcePool_AllocateElement(resourcePool& pool);

inline void ResourcePool_ReleaseElement(resourcePool& pool, const size_t index) {
    if (index >= pool.Resources.Size) return;
    DynamicArray_PushBack(&pool.FreeIndices, &index);
}

inline size_t ResourcePool_AddElement(resourcePool& pool, const void* element) {
    const size_t slot = ResourcePool_AllocateElement(pool);
    DynamicArray_Set(&pool.Resources, slot, element);
    return slot;
}

inline bool ResourcePool_IsEmpty(const resourcePool& pool) {
    return pool.FreeIndices.Size == 0;
}

inline bool ResourcePool_Reserve(resourcePool& pool, const size_t minCapacity) {
    return DynamicArray_Reserve(&pool.Resources, minCapacity);
}

inline bool ResourcePool_Reserve(resourcePool& pool, const size_t resourceCapacity, const size_t freeIndicesCapacity) {
    const bool resourcesReserved = DynamicArray_Reserve(&pool.Resources, resourceCapacity);
    const bool freeIndicesReserved = DynamicArray_Reserve(&pool.FreeIndices, freeIndicesCapacity);
    return resourcesReserved && freeIndicesReserved;
}
