#include <Engine/Factory/ComponentFactory.hpp>

ComponentFactory::ComponentFactory() {}

void ComponentFactory::Allocate(const RTTI::type& rtti, const Entity& entity) {
  MAP(ALLOC_COMPONENT, Transform, Velocity, Collider, Renderer)
}

void ComponentFactory::Free(const RTTI::type& rtti, const Entity& entity) {
  MAP(FREE_COMPONENT, Transform, Velocity, Collider, Renderer)
}

void ComponentFactory::FreeEntity(const Entity& entity) {
  for (auto const& x : componentArrays) {
    Free(x.first, entity);
  }
}

template <typename T> T* ComponentFactory::Get(const Entity& entity) const {
  const RTTI::type& typeName = T::rtti.id();
  assert(componentArrays.find(typeName) == componentArrays.end() && "Registering component type more than once.");

  return GetComponentPool<T>()[entity];
}

template <typename T> std::shared_ptr<Pool<T>> ComponentFactory::GetComponentPool() {
  const RTTI::type& typeName = T::rtti.id();
  assert(componentArrays.find(typeName) != componentArrays.end() && "Component not registered before use.");

  return std::static_pointer_cast<Pool<T>>(componentArrays[typeName]);
}
