#include <Engine/Common/Log.hpp>
#include <Engine/System/LogicalSystem.hpp>

RTTI_DEFINITION(LogicalSystem, ISystem)

void LogicalSystem::update(Context& context) {
  LOG(LOG_INFO, "[LogicalSystem] Update!");
  /**
   * @todo Mettre ici la logique: comportements, déplacements, animations etc...
   * Certains objets doivent toujours être updaté tandis que
   * d’autres sont en pause lorsqu’ils sont trop éloignés.
   */
}