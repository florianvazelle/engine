#include <Engine/System/LogicalSystem.hpp>

#include <Engine/Common/Log.hpp>

RTTI_DEFINITION(LogicalSystem, System)

void LogicalSystem::update(double deltaTime) {
  LOG("update!");
  /**
   * @todo Mettre ici la logique: comportements, déplacements, animations etc...
   * Certains objets doivent toujours être updaté tandis que
   * d’autres sont en pause lorsqu’ils sont trop éloignés.
   */
}