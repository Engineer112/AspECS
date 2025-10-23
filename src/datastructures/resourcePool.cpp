//
// Created by Hosea on 10/23/2025.
//

#include "datastructures/resourcePool.h"

size_t ResourcePool_AllocateElement(resourcePool& pool) {
    size_t slot;

    // Case 1: reuse previously freed slot
    if (pool.FreeIndices.Size > 0) {
        DynamicArray_PopBack(&pool.FreeIndices, &slot);
        assert(slot < pool.Resources.Size && "Corrupt free list!");
    }
    // Case 2: allocate a new slot at the end
    else {
        slot = pool.Resources.Size;
        DynamicArray_PushBack(&pool.Resources, nullptr);
    }

    return slot;
}
