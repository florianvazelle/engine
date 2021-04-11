#include <Engine/Common/Log.hpp>
#include <Engine/System/PhysicalSystem.hpp>

RTTI_DEFINITION(PhysicalSystem, ISystem)

void PhysicalSystem::update(Context& context) {
  LOG(LOG_INFO, "[PhysicalSystem] Update!");
  /**
   * @todo Mettre ici la simulation physique: détection de collisions, résolution des
   * pénétrations et des interactions. Les objets éloignés ou qui
   * ne subissent pas de force ou restitution sont endormis.
   */
}