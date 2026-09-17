#include <gtest/gtest.h>

#include "entity_id.hpp"

using namespace brasa;

TEST(Entity, NullEntity_IsNull) {
    EXPECT_TRUE(ecs::entity_is_null(ecs::ENTITY_NULL));
}

TEST(Entity, ValidEntity_IsNotNull) {
    EXPECT_FALSE(ecs::entity_is_null(ecs::entity_build(1, 0)));
}

TEST(Entity, BuildEntity_KeepsIndexAndGeneration) {
    auto entity_id = ecs::entity_build(1, 2);
    ASSERT_EQ(ecs::entity_index(entity_id), 1);
    ASSERT_EQ(ecs::entity_gen(entity_id), 2);
}