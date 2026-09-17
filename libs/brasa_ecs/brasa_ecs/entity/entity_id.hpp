#pragma once

#include <cstdint>

namespace brasa::ecs {
    // EntityId — 64-bit handle.
    //
    //  [63 ............. 48 | 47 .......... 32 | 31 .............. 0]
    //  [  [EMPTY FOR NOW]   |  generation (16) |     index (32)     ]
    using EntityId = uint64_t;
    using EntityIndex = uint32_t;
    using EntityGen = uint16_t;

    inline constexpr EntityId ENTITY_NULL = 0;

    inline constexpr uint64_t ENTITY_INDEX_MASK = 0x00000000FFFFFFFFULL;
    inline constexpr uint64_t ENTITY_GEN_MASK   = 0x0000FFFF00000000ULL;
    inline constexpr uint64_t ENTITY_GEN_SHIFT  = 32;

    constexpr EntityId entity_build(const EntityIndex index, const EntityGen generation) {
        return
            static_cast<uint64_t>(generation) << ENTITY_GEN_SHIFT
            | index;
    }

    constexpr EntityIndex entity_index(const EntityId id) {
        return static_cast<uint32_t>(id & ENTITY_INDEX_MASK);
    }

    constexpr EntityGen entity_gen(const EntityId id) {
        return static_cast<uint16_t>((id & ENTITY_GEN_MASK) >> ENTITY_GEN_SHIFT);
    }

    constexpr bool entity_is_null(const EntityId id) {
        return id == ENTITY_NULL;
    }

    /// Lifecycle of an EntityId.
    enum class EntityState : uint8_t {
        Unallocated, /// Index/generation not issued yet.
        Allocated,   /// Reserved (or reservable) - a valid handle, but not yet spawned.
        Spawned,     /// Alive and queryable.
        Freed,       /// Stale handle - its index has moved on to a later generation.
    };

    // ----------------------

    using Id = uint64_t;
}
