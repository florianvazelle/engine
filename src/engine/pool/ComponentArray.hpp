#pragma once

#include <array>
#include <engine/ecs/Entity.hpp>
#include <engine/pool/Pool.hpp>

template <typename T>
class ComponentArray : public IPool {
 public:
  void Allocate(const Entity& entity) {
    if (entity < MAX_ENTITIES && !componentIsSet[entity]) {
      // datnum[entity] = T();
      componentIsSet[entity] = true;
    }
  }

  void Free(const Entity& entity) {
    if (entity < MAX_ENTITIES && componentIsSet[entity]) {
      datnum[entity].T::~T();
      componentIsSet[entity] = false;
    }
  }

  void* Get(const Entity& entity) {
    if (componentIsSet[entity])
      return &(datnum[entity]);
    else
      return nullptr;
  }

 private:
  std::array<T, MAX_ENTITIES> datnum;
  std::array<bool, MAX_ENTITIES> componentIsSet;
};