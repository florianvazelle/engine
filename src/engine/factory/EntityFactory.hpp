#pragma once

#include <any>
#include <array>
#include <cassert>
#include <engine/ecs/Entity.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

class Registry;

/**
 * @brief Permet de gérer l'allocation/libération des Entity
 */
class EntityFactory {
 public:
  /**
   * @brief Initialise la queue avec toute les Entity possible
   */
  EntityFactory() : livingEntityCount(0) {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
      availableEntities.push(entity);
      entityIsSet[entity] = false;
    }
  }

  /**
   * @brief Ajoute d'une Entity
   * @return L'identifiant de l'Entity
   */
  Entity Allocate() {
    assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;

    entityIsSet[id] = true;

    return id;
  }

  /**
   * @brief Supprime l'Entity
   */
  void Free(const Entity& entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    availableEntities.push(entity);
    --livingEntityCount;

    entityIsSet[entity] = false;
  }

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