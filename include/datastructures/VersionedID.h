//
// Created by Hosea on 10/20/2025.
//

#pragma once
#include <cstdint>

using versionedID = uint64_t;

constexpr uint64_t ENTITY_VERSION_BITS = 32;
constexpr uint64_t VERSION_MASK = 0xFFFFFFFF;

inline versionedID BuildVersionedID(const uint32_t id, const uint32_t version) {
    return static_cast<versionedID>((static_cast<uint64_t>(id) << ENTITY_VERSION_BITS) | version);
}

inline uint32_t ExtractID(const versionedID entity) {
    return static_cast<uint32_t>((entity >> ENTITY_VERSION_BITS) & VERSION_MASK);
}

inline uint32_t ExtractVersion(const versionedID entity) {
    return static_cast<uint32_t>(entity & VERSION_MASK);
}