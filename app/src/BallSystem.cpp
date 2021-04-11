#include <BallSystem.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Transform.hpp>
#include <Velocity.hpp>

RTTI_DEFINITION(BallSystem, ISystem)

void BallSystem::update(Context& context) {
  LOG(LOG_INFO, "--- Ball Update ---");

  // // Get the Manager
  // Manager* man = Manager::GetInstance();
  // // Get all Entity with Transform and Velocity Component
  // man->GetObjectsWithTag(man->entitiesQuery, Transform::rtti, Velocity::rtti);

  // // Iterate on entitites
  // man->results.resize(man->entitiesQuery.size());
  // for (unsigned int i = 0; i < man->entitiesQuery.size(); i++) {
  //   // For each Entity, add a task to the ThreadPool
  //   man->results[i] = man->threadPool.push(
  //       [&](const Entity& entity) {

  //         // Update the Transform with Velocity
  //         Transform* t = man->GetComponent<Transform>(entity);
  //         Velocity* v = man->GetComponent<Velocity>(entity);

  //         t->translate(v->direction);
  //       },
  //       man->entitiesQuery[i]);
  // }

  // // Join all thread
  // for (auto&& result : man->results) result.get();
}