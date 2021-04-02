#pragma once

#include <any>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Pool/Pool.hpp>

/**
 * @brief Permet de gérer l'allocation/libération des Entity
 */
class EntityFactory {
public:
  /**
   * @brief Initialise la queue avec toute les Entity possible
   */
  EntityFactory();

  /**
   * @brief Ajoute d'une Entity
   * @return L'identifiant de l'Entity
   */
  Entity Allocate();

  /**
   * @brief Supprime l'Entity
   */
  void Free(const Entity& entity);

  /**
   * @brief Indique si l'Entity correspondante est créé
   * @return Retourne vrai si l'Entity est créé
   */
  bool IsSet(const Entity& entity) const { return entityIsSet[entity]; }

private:
  std::array<bool, MAX_ENTITIES> entityIsSet;
  std::queue<Entity> availableEntities{};  // Queue des Entity disponibles
  uint32_t livingEntityCount{};            // Total des Entity en "vie"
};