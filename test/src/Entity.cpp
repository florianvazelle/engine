
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

// TEST_CASE("Alloc Entity") {
//   //   MAP(REGISTER_COMPONENT, Transform, Velocity, Collider, Renderer)

//   Manager* man = Manager::GetInstance();
//   Entity test  = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
//   man->FreeEntity(test);

//   CHECK(man->GetComponent<Transform>(test) == nullptr);
//   CHECK(man->GetComponent<Velocity>(test) == nullptr);
//   CHECK(man->GetComponent<Collider>(test) == nullptr);
//   CHECK(man->GetComponent<Renderer>(test) == nullptr);
// }
