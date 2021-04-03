#include <BallSystem.hpp>

#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Transform.hpp>
#include <Velocity.hpp>

RTTI_DEFINITION(BallSystem, System)

void BallSystem::update(double deltaTime) {
  LOG("--- Ball Update ---");
  Manager* man = Manager::GetInstance();
  man->GetObjectsWithTag(entitiesQuery, Transform::rtti, Velocity::rtti);

  results.resize(entitiesQuery.size());
  for (int i = 0; i < entitiesQuery.size(); i++) {
    results[i] = thread_pool.push(
        [&](const Entity& entity) {
          Transform* t = man->GetComponent<Transform>(entity);
          Velocity* v  = man->GetComponent<Velocity>(entity);

          t->translate(v->x, v->y, v->z, v->w);
        },
        entitiesQuery[i]);
  }

  for (auto&& result : results) result.get();
}