#pragma once

#include <engine/component/ICollider.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/factory/Registry.hpp>

class PhysicalSystem : public ISystem {
 public:
  RTTI_DEFINITION(PhysicalSystem, ISystem)
  ~PhysicalSystem() {}

  void update() const {
    LOG(LOG_INFO, "[PhysicalSystem] Update!");
    /**
     * @todo Mettre ici la simulation physique: détection de collisions,
     * résolution des pénétrations et des interactions. Les objets éloignés ou
     * qui ne subissent pas de force ou restitution sont endormis.
     */

    Registry* registry = Registry::GetInstance();
    registry->GetObjectsWithParentTag<ICollider>(registry->entitiesQuery);

    registry->results.resize(registry->entitiesQuery.size() - 1);
    for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
      for (unsigned int j = i + 1; j < registry->entitiesQuery.size(); j++) {
        ICollider* icoll = registry->GetComponentWithParent<ICollider>(
            registry->entitiesQuery[i]);
        registry->results[i] = registry->threadPool.push(
            [](ICollider* coll, const Entity& e1, const Entity& e2) {
              coll->intersect(e1, e2);
            },
            icoll, registry->entitiesQuery[i], registry->entitiesQuery[j]);
      }
    }

    for (auto&& result : registry->results) result.get();
  }
};