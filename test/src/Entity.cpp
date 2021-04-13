
#include <doctest.h>

#include <Engine/Common/Manager.hpp>
#include <Engine/Core/Context.hpp>

TEST_CASE("GetObjectsWithTag") {
  REGISTER_COMPONENTS

  Manager* man = Manager::GetInstance();
  Entity test1 = man->AllocateEntity();
  Entity test2 = man->AllocateEntity(Transform::rtti);
  Entity test3 = man->AllocateEntity(Transform::rtti);
  Entity test4 = man->AllocateEntity(Transform::rtti, Velocity::rtti);

  std::vector<Entity> entities(10);
  man->GetObjectsWithTag(entities);

  CHECK(entities.size() == 4);
  CHECK(entities[0] == test1);
  CHECK(entities[1] == test2);
  CHECK(entities[2] == test3);
  CHECK(entities[3] == test4);

  man->GetObjectsWithTag(entities, Velocity::rtti);
  CHECK(entities.size() == 1);
  CHECK(entities[0] == test4);

  man->GetObjectsWithTag(entities, Transform::rtti, Velocity::rtti);
  CHECK(entities.size() == 1);
  CHECK(entities[0] == test4);

  man->GetObjectsWithTag(entities, Transform::rtti);
  CHECK(entities.size() == 3);
  CHECK(entities[0] == test2);
  CHECK(entities[1] == test3);
  CHECK(entities[2] == test4);
}

class TestRenderer : public IRenderer {
 public:
  RTTI_DECLARATION
  ~TestRenderer() = default;

  void render(const Context& context, const Entity& entity) {}
};

RTTI_DEFINITION(TestRenderer, IRenderer)

TEST_CASE("GetObjectsWithParentTag") {
  REGISTER_COMPONENT(TestRenderer)

  Manager* man = Manager::GetInstance();
  Entity test = man->AllocateEntity(Transform::rtti, TestRenderer::rtti);

  std::vector<Entity> entities(10);
  man->GetObjectsWithParentTag<IRenderer>(entities);

  CHECK(entities.size() == 1);
  CHECK(entities[0] == test);
}

TEST_CASE("Alloc Entity") {
  Manager* man = Manager::GetInstance();
  Entity test = man->AllocateEntity(Transform::rtti);

  CHECK(man->GetComponent<Transform>(test) != nullptr);
  CHECK(man->GetComponent<Velocity>(test) == nullptr);

  man->FreeEntity(test);
}

TEST_CASE("Alloc Entity") {
  Manager* man = Manager::GetInstance();
  Entity test = man->AllocateEntity(Transform::rtti, Velocity::rtti);
  man->FreeEntity(test);

  CHECK(man->GetComponent<Transform>(test) == nullptr);
  CHECK(man->GetComponent<Velocity>(test) == nullptr);
}
