#include <Engine/Component/Collider.hpp>

RTTI_DEFINITION(Collider, IComponent)

bool Collider::intersect(Transform trans) { return false; }