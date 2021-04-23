#include <SDL_rect.h>

#include <Engine/Common/Dispatcher.hpp>
#include <Engine/Common/Registry.hpp>
#include <Engine/Component/RectCollider.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Event/Collide.hpp>

RTTI_DEFINITION(RectCollider, ICollider)

void RectCollider::intersect(const Entity& e1, const Entity& e2) {
  Registry* registry = Registry::GetInstance();

  Transform* trans1 = registry->GetComponent<Transform>(e1);
  Transform* trans2 = registry->GetComponent<Transform>(e2);

  if (trans1->intersect(*trans2)) {
    Dispatcher* dispatcher = Dispatcher::GetInstance();
    dispatcher->Trigger(Collide(e1, e2));
  }
}