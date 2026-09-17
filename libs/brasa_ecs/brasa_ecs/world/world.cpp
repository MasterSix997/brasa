#include "world.hpp"

#include <atomic>

namespace brasa::ecs {
    class WorldImpl {
    public:
        std::atomic<uint32_t> ref_count{0};
    };

    World::World() {
        m_impl = new WorldImpl;
        m_impl->ref_count.fetch_add(1, std::memory_order_relaxed);
    }

    World::World(WorldImpl* impl) : m_impl(impl) {
        if (impl)
            m_impl->ref_count.fetch_add(1, std::memory_order_relaxed);
    }

    World::World(const World& other) : m_impl(other.m_impl) {
        if (m_impl)
            m_impl->ref_count.fetch_add(1, std::memory_order_relaxed);
    }

    World& World::operator=(const World& other) {
        if (this != &other) {
            if (m_impl && m_impl->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
                delete m_impl;

            m_impl = other.m_impl;
            if (m_impl)
                m_impl->ref_count.fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }

    World::World(World&& other) noexcept : m_impl(other.m_impl) {
        other.m_impl = nullptr;
    }

    World& World::operator=(World&& other) noexcept {
        if (this != &other) {
            if (m_impl && m_impl->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
                delete m_impl;

            m_impl = other.m_impl;
            other.m_impl = nullptr;
        }
        return *this;
    }

    World::~World() {
        if (m_impl && m_impl->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
            delete m_impl;
    }

}
