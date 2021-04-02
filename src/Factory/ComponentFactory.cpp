#include <Engine/Factory/ComponentFactory.hpp>

ComponentFactory::ComponentFactory() {}

void ComponentFactory::Allocate(const RTTI::type& rtti, const Entity& entity) { MAP_COMPONENT(ALLOC_COMPONENT) }

void ComponentFactory::Free(const RTTI::type& rtti, const Entity& entity) { MAP_COMPONENT(FREE_COMPONENT) }

void ComponentFactory::FreeEntity(const Entity& entity) {
  for (auto const& x : componentArrays) {
    Free(x.first, entity);
  }
}