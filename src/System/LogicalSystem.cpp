#include <Engine/System/LogicalSystem.hpp>
#include <Engine/Util/Log.hpp>

RTTI_DEFINITION(LogicalSystem, ISystem)

void LogicalSystem::update() const {
  LOG(LOG_INFO, "[LogicalSystem] Update!");
  /**
   * @todo Mettre ici la logique: comportements, déplacements, animations etc...
   * Certains objets doivent toujours être updaté tandis que
   * d’autres sont en pause lorsqu’ils sont trop éloignés.
   */
}