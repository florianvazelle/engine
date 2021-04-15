#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/ICollider.hpp>
#include <Engine/System/PhysicalSystem.hpp>

RTTI_DEFINITION(PhysicalSystem, ISystem)

void PhysicalSystem::update() const {
  LOG(LOG_INFO, "[PhysicalSystem] Update!");
  /**
   * @todo Mettre ici la simulation physique: détection de collisions, résolution des
   * pénétrations et des interactions. Les objets éloignés ou qui
   * ne subissent pas de force ou restitution sont endormis.
   */

  // Manager* man = Manager::GetInstance();
  // man->GetObjectsWithParentTag<ICollider>(man->entitiesQuery);

  // man->results.resize(man->entitiesQuery.size());
  // for (unsigned int i = 0; i < man->entitiesQuery.size(); i++) {
  //   for (unsigned int j = 0; j < man->entitiesQuery.size(); j++) {
  //     if (i == j) continue;

  //     ICollider* icoll = man->GetComponentWithParent<ICollider>(man->entitiesQuery[i]);
  //     man->results[i] = man->threadPool.push(
  //         [](ICollider* coll, const Entity& e1, const Entity& e2) { coll->intersect(e1, e2); },
  //         icoll, man->entitiesQuery[i], man->entitiesQuery[j]);
  //   }
  // }

  // for (auto&& result : man->results) result.get();
}