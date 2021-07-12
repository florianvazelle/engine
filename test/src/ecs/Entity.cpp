
#include <doctest.h>

#include <engine/engine.hpp>
#include <iostream>

TEST_CASE("GetEntitiesWithTags") {
  REGISTER_COMPONENTS

  Registry* registry = Registry::GetInstance();
  Entity test1 = registry->AllocateEntity();
  Entity test2 = registry->AllocateEntity(Transform::rtti);
  Entity test3 = registry->AllocateEntity(Transform::rtti);
  Entity test4 = registry->AllocateEntity(Transform::rtti, Velocity::rtti);

  std::vector<Entity> entities(10);
  registry->GetEntitiesWithTags(entities);

  CHECK(entities.size() == 4);
  CHECK(entities[0] == test1);
  CHECK(entities[1] == test2);
  CHECK(entities[2] == test3);
  CHECK(entities[3] == test4);

  registry->GetEntitiesWithTags(entities, Velocity::rtti);
  CHECK(entities.size() == 1);
  CHECK(entities[0] == test4);

  registry->GetEntitiesWithTags(entities, Transform::rtti, Velocity::rtti);
  CHECK(entities.size() == 1);
  CHECK(entities[0] == test4);

  registry->GetEntitiesWithTags(entities, Transform::rtti);
  CHECK(entities.size() == 3);
  CHECK(entities[0] == test2);
  CHECK(entities[1] == test3);
  CHECK(entities[2] == test4);
}

TEST_CASE("Alloc Entity") {
  Registry* registry = Registry::GetInstance();
  Entity test = registry->AllocateEntity(Transform::rtti);

  CHECK(registry->GetComponent<Transform>(test) != nullptr);
  CHECK(registry->GetComponent<Velocity>(test) == nullptr);

  registry->FreeEntity(test);
}

TEST_CASE("Alloc Entity") {
  Registry* registry = Registry::GetInstance();
  Entity test = registry->AllocateEntity(Transform::rtti, Velocity::rtti);
  registry->FreeEntity(test);

  CHECK(registry->GetComponent<Transform>(test) == nullptr);
  CHECK(registry->GetComponent<Velocity>(test) == nullptr);
}
