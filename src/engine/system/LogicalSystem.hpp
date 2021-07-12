#pragma once

#include <engine/ecs/Entity.hpp>
#include <engine/ecs/ISystem.hpp>
#include <vector>

class LogicalSystem : public ISystem {
 public:
  RTTI_DEFINITION(LogicalSystem, ISystem)
  ~LogicalSystem() {}

  void update() const {
    LOG(LOG_INFO, "[LogicalSystem] Update!");
    /**
     * @todo Mettre ici la logique: comportements, déplacements, animations
     * etc... Certains objets doivent toujours être updaté tandis que d’autres
     * sont en pause lorsqu’ils sont trop éloignés.
     */
  }
};