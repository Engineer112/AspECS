//
// Created by Hosea on 10/20/2025.
//

#pragma once

#include "../datastructures/VersionedID.h"
#include "../datastructures/dynamicArray.h"

using Entity = versionedID;

inline Entity BuildEntity(const uint32_t id, const uint32_t version) {
    return BuildVersionedID(id, version);
}

struct EntityInfo {
    int64_t data; // archetype (high), column (low)
    uint32_t activeVersion;
    bool active;
};

inline uint32_t ExtractDataColumn(const EntityInfo& info) {
    return static_cast<uint32_t>(info.data & 0xFFFFFFFF);
}

inline uint32_t ExtractArchetype(const EntityInfo& info) {
    return static_cast<uint32_t>(info.data >> 32);
}

inline int64_t CombineEntityData(const uint32_t column, const uint32_t archetype) {
    return static_cast<int64_t>(column) << 32 | static_cast<int64_t>(archetype);
}

inline void SetData(EntityInfo& info, const uint32_t column, const uint32_t archetype) {
    info.data = CombineEntityData(column, archetype);
}


struct EntityManager {
    DynamicArray Data;
};

void InitEntityManager();

Entity CreateEntity(const EntityManager& manager);
void DestroyEntity(Entity entity);