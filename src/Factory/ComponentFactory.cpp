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