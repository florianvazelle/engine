#pragma once

#include <SDL_rect.h>

#include <engine/component/ICollider.hpp>
#include <engine/component/Transform.hpp>
#include <engine/event/Collide.hpp>
#include <engine/factory/Dispatcher.hpp>
#include <engine/factory/Registry.hpp>

class RectCollider final : public ICollider {
 public:
  RTTI_DEFINITION(RectCollider, ICollider)
  ~RectCollider() {}

  void intersect(const Entity& e1, const Entity& e2) const {
    Registry* registry = Registry::GetInstance();

    Transform* trans1 = registry->GetComponent<Transform>(e1);
    Transform* trans2 = registry->GetComponent<Transform>(e2);

    if (trans1->intersect(*trans2)) {
      Dispatcher* dispatcher = Dispatcher::GetInstance();
      dispatcher->Trigger(Collide(e1, e2));
    }
  }
};