#include <Engine/Factory/EntityFactory.hpp>

EntityFactory::EntityFactory() : livingEntityCount(0) {
  for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
    availableEntities.push(entity);
  }
}

Entity EntityFactory::Allocate() {
  assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

  // Take an ID from the front of the queue
  Entity id = availableEntities.front();
  availableEntities.pop();
  ++livingEntityCount;

  return id;
}

void EntityFactory::Free(const Entity& entity) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");

  availableEntities.push(entity);
  --livingEntityCount;
}