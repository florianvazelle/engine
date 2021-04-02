
#include <doctest/doctest.h>

#include <Engine/Common/Manager.hpp>

TEST_CASE("Alloc Entity") {
  MAP(REGISTER_COMPONENT, Transform, Velocity, Collider, Renderer)

  Manager* man = Manager::GetInstance();
  Entity test  = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);

  CHECK(test == 0);

  CHECK(man->GetComponent<Transform>(test) != nullptr);
  CHECK(man->GetComponent<Velocity>(test) == nullptr);
  CHECK(man->GetComponent<Collider>(test) != nullptr);
  CHECK(man->GetComponent<Renderer>(test) != nullptr);
}

TEST_CASE("Alloc Entity") {
  // MAP(REGISTER_COMPONENT, Transform, Velocity, Collider, Renderer)

  Manager* man = Manager::GetInstance();
  Entity test  = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
  man->FreeEntity(test);

  CHECK(man->GetComponent<Transform>(test) == nullptr);
  CHECK(man->GetComponent<Velocity>(test) == nullptr);
  CHECK(man->GetComponent<Collider>(test) == nullptr);
  CHECK(man->GetComponent<Renderer>(test) == nullptr);
}

// TEST_CASE("GetObjectsWithTag") {
//   // MAP(REGISTER_COMPONENT, Transform, Velocity, Collider, Renderer)

//   Manager* man = Manager::GetInstance();
//   Entity test1 = man->AllocateEntity();
//   Entity test2 = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
//   Entity test3 = man->AllocateEntity(Transform::rtti, Renderer::rtti);
//   Entity test4 = man->AllocateEntity(Transform::rtti, Velocity::rtti);

//   std::vector<Entity> entities(10);
//   man->GetObjectsWithTag(entities);

//   CHECK(entities.size() == 4);
//   CHECK(entities[0] == test1);
//   CHECK(entities[1] == test2);
//   CHECK(entities[2] == test3);
//   CHECK(entities[3] == test4);

//   man->GetObjectsWithTag(entities, Velocity::rtti);
//   CHECK(entities.size() == 1);
//   CHECK(entities[0] == test4);

//   man->GetObjectsWithTag(entities, Transform::rtti, Velocity::rtti);
//   CHECK(entities.size() == 1);
//   CHECK(entities[0] == test4);

//   man->GetObjectsWithTag(entities, Transform::rtti);
//   CHECK(entities.size() == 3);
//   CHECK(entities[0] == test2);
//   CHECK(entities[1] == test3);
//   CHECK(entities[2] == test4);
// }
