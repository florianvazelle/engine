#include <Engine/Factory/ComponentFactory.hpp>

ComponentFactory::ComponentFactory() {}

void ComponentFactory::Allocate(const RTTI::type& rtti, const Entity& entity) {
  assert(componentArrays.find(rtti) != componentArrays.end() && "We cannot allocate a unknow Component.");
  componentArrays[rtti]->Allocate(entity);
}

void ComponentFactory::Free(const RTTI::type& rtti, const Entity& entity) {
  assert(componentArrays.find(rtti) != componentArrays.end() && "We cannot free a unknow Component.");
  componentArrays[rtti]->Free(entity);
}

void ComponentFactory::FreeEntity(const Entity& entity) {
  for (auto const& x : componentArrays) {
    Free(x.first, entity);
  }
}