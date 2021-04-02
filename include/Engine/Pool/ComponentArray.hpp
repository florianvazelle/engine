#pragma once

template <typename T> class ComponentArray : public IPool {
public:
  template <typename... Args> void Allocate(const Entity& entity, Args&&... args) {
    if (entity < MAX_ENTITIES && !componentIsSet[entity]) {
      datnum[entity]         = T(std::forward<Args>(args)...);
      componentIsSet[entity] = true;
    }
  }

  void Free(const Entity& entity) {
    if (entity < MAX_ENTITIES && componentIsSet[entity]) {
      datnum[entity].T::~T();
      componentIsSet[entity] = false;
    }
  }

  T* Get(const Entity& entity) {
    if (componentIsSet[entity])
      return &(datnum[entity]);
    else
      return nullptr;
  }

private:
  std::array<T, MAX_ENTITIES> datnum;
  std::array<bool, MAX_ENTITIES> componentIsSet;
};