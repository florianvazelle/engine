#include <Engine/Common/Registry.hpp>
#include <Engine/Component/ICollider.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/Util/Log.hpp>

RTTI_DEFINITION(PhysicalSystem, ISystem)

void PhysicalSystem::update() const {
  LOG(LOG_INFO, "[PhysicalSystem] Update!");
  /**
   * @todo Mettre ici la simulation physique: détection de collisions, résolution des
   * pénétrations et des interactions. Les objets éloignés ou qui
   * ne subissent pas de force ou restitution sont endormis.
   */

  // Registry* registry = Registry::GetInstance();
  // registry->GetObjectsWithParentTag<ICollider>(registry->entitiesQuery);

  // registry->results.resize(registry->entitiesQuery.size());
  // for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
  //   for (unsigned int j = 0; j < registry->entitiesQuery.size(); j++) {
  //     if (i == j) continue;

  //     ICollider* icoll = registry->GetComponentWithParent<ICollider>(registry->entitiesQuery[i]);
  //     registry->results[i] = registry->threadPool.push(
  //         [](ICollider* coll, const Entity& e1, const Entity& e2) { coll->intersect(e1, e2); },
  //         icoll, registry->entitiesQuery[i], registry->entitiesQuery[j]);
  //   }
  // }

  // for (auto&& result : registry->results) result.get();
}