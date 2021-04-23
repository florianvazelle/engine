#include <SDL_rect.h>

#include <Engine/Common/Registry.hpp>
#include <Engine/Component/RectCollider.hpp>
#include <Engine/Component/Transform.hpp>

RTTI_DEFINITION(RectCollider, ICollider)

bool RectCollider::intersect(const Entity& e1, const Entity& e2) {
  Registry* registry = Registry::GetInstance();

  Transform* trans1 = registry->GetComponent<Transform>(e1);
  Transform* trans2 = registry->GetComponent<Transform>(e2);

  if (trans1->intersect(*trans2)) {
    Velocity* v1 = registry->GetComponent<Velocity>(e1);
    if (v1 != nullptr) {
      v1->direction = -(v1->direction);
      LOG(LOG_WARNING, "Intersect e1=" + std::to_string(e1) + " - e2=" + std::to_string(e2));
    }

    Velocity* v2 = registry->GetComponent<Velocity>(e2);
    if (v2 != nullptr) {
      v2->direction = -(v2->direction);
      LOG(LOG_WARNING, "Intersect e1=" + std::to_string(e1) + " - e2=" + std::to_string(e2));
    }

    return true;
  }
  return false;
}