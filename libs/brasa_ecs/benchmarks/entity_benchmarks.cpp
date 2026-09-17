#include <brasa_ecs/brasa_ecs.hpp>

#include <benchmark/benchmark.h>

static void EntityIsNull(benchmark::State &state) {
  brasa::ecs::EntityId entity = brasa::ecs::ENTITY_NULL;
  for (auto _ : state) {
    benchmark::DoNotOptimize(brasa::ecs::entity_is_null(entity));
    ++entity;
  }
}
BENCHMARK(EntityIsNull);
