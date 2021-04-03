#include <Engine/System/PhysicalSystem.hpp>

#include <Engine/Common/Log.hpp>

RTTI_DEFINITION(PhysicalSystem, System)

void PhysicalSystem::update(double deltaTime) {
  LOG("Update!");
  /**
   * @todo Mettre ici la simulation physique: détection de collisions, résolution des
   * pénétrations et des interactions. Les objets éloignés ou qui
   * ne subissent pas de force ou restitution sont endormis.
   */
}