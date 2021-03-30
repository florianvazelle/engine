#include <Engine/Component/Collider.hpp>

RTTI_DEFINITION(Collider, Component)

bool Collider::intersect(Transform trans) { return false; }