//
// Created by Hosea on 10/20/2025.
//
#include "../../include/World/EntityManager.h"
#include "datastructures/dynamicArray.h"

Entity CreateEntity(EntityManager &manager) {
    const uint32_t id = manager.Data.Size;
    constexpr uint32_t version = 0;

    EntityInfo newEntityInfo{};
    newEntityInfo.active = true;
    newEntityInfo.activeVersion = version;
    newEntityInfo.data = -1;

    DynamicArray_PushBack(&manager.Data, &newEntityInfo);

    return BuildEntity(id, version);
}

void InitEntityManager() {

}

void DestroyEntity(Entity entity) {
}
