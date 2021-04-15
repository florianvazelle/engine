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
    return true;
  }
  return false;
}