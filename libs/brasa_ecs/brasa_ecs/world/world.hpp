#pragma once
#include <cstddef>

namespace brasa::ecs {
    class WorldImpl;

    class World {
    public:
        World();
        explicit World(WorldImpl* impl);
        World(std::nullptr_t) noexcept : m_impl(nullptr) {}
        World(const World& other);
        World& operator=(const World& other);
        World(World&& other) noexcept;
        World& operator=(World&& other) noexcept;
        ~World();

        [[nodiscard]] bool valid() const { return m_impl != nullptr; }

    private:
        WorldImpl* m_impl;
    };
}
