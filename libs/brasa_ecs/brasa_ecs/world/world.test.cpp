#include <gtest/gtest.h>

#include "world.hpp"

using namespace brasa;

TEST(World, DefaultWorldConstructor_IsValid) {
    ecs::World world;
    ASSERT_TRUE(world.valid());
}

TEST(World, NullPtrWorldConstructor_IsNotValid) {
    ecs::World world {nullptr};
    ASSERT_FALSE(world.valid());
}

TEST(World, CopyWorld_BothValid) {
    ecs::World world1;
    auto world2 = world1; // NOLINT(*-unnecessary-copy-initialization)
    ASSERT_TRUE(world1.valid());
    ASSERT_TRUE(world2.valid());
}

TEST(World, MoveWorld_BecomeInvalid) {
    ecs::World world1;
    auto world2 = std::move(world1);
    ASSERT_FALSE(world1.valid());
    ASSERT_TRUE(world2.valid());
}