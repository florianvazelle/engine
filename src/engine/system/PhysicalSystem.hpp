#pragma once

#include <SDL_rect.h>

#include <engine/component/Transform.hpp>
#include <engine/component/collider/RectCollider.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/event/Collide.hpp>
#include <engine/event/Dispatcher.hpp>
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
    registry->GetEntitiesWithTags(registry->entitiesQuery, RectCollider::rtti);

    registry->results.resize(registry->entitiesQuery.size() - 1);
    for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
      for (unsigned int j = i + 1; j < registry->entitiesQuery.size(); j++) {
        registry->results[i] = registry->threadPool.push(
            [](const Entity& e1, const Entity& e2) {
              //
              // Begin Intersection Between Two Rect
              Registry* registry = Registry::GetInstance();

              Transform* trans1 = registry->GetComponent<Transform>(e1);
              Transform* trans2 = registry->GetComponent<Transform>(e2);

              if (trans1->intersect(*trans2)) {
                Dispatcher* dispatcher = Dispatcher::GetInstance();
                dispatcher->Trigger(Collide(e1, e2));
              }
              // End
              //
            },
            registry->entitiesQuery[i], registry->entitiesQuery[j]);
      }
    }

    for (auto&& result : registry->results) result.get();
  }
};