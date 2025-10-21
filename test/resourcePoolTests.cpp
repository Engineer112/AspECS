//
// Created by Hosea on 10/21/2025.
//
#include "datastructures/resourcePool.h"
#include "gtest/gtest.h"

TEST(ResourcePoolTests, InitAndFree) {
    resourcePool pool{};

    ResourcePool_Init(pool, 4, 4);

    EXPECT_TRUE(pool.Resources.Data != nullptr);
    ResourcePool_Destroy(pool);
    EXPECT_TRUE(pool.Resources.Data == nullptr);
}