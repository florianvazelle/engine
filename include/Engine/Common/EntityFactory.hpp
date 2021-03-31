#pragma once

#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Common/ComponentFactory.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Pool/Pool.hpp>
#include <Engine/Common/Entity.hpp>

#define MAX_ENTITIES 10

class EntityFactory {
public:
  EntityFactory() : entities(MAX_ENTITIES), trans_pool(MAX_ENTITIES), velo_pool(MAX_ENTITIES), coll_pool(MAX_ENTITIES), rend_pool(MAX_ENTITIES) {}
  EntityFactory(size_t arena_size) : entities(arena_size), trans_pool(arena_size), velo_pool(arena_size), coll_pool(arena_size), rend_pool(arena_size) {}

  /**
   * @brief Ajoute d'une entité, à la Pool d'entitée
   * @param args Liste d'argument pour initaliser une entité
   * @return Pointeur vers l'entité alloué
   */
  template <typename... Args> Entity *Allocate(Args &&... args) {
    Pool<Entity> &a = GetObjects();
    return a.alloc(std::forward<Args>(args)...);
  }

  /**
   * @brief Permet de récupérer toutes les entitées alloué
   * @return Retourne la Pool d'entité
   */
  inline Pool<Entity> &GetObjects() { return entities; }
  inline const Pool<Entity> &GetObjects() const { return entities; }

  template <typename... Args> void GetObjectsWithTag(std::vector<Entity *> &entities, Args &&... args) {
    int idx = 0;

    // On récupère la Pool d'entité
    Pool<Entity> &a = GetObjects();

    // On parcours ensuite la Pool
    for (typename Pool<Entity>::iterator it = a.begin(); it != a.end(); it = a.next(it)) {
      bool result = true;

      Entity* entity = it->get_storage();

      // On parcours l'ensemble des types -> args
      // ([&](auto &arg) { result &= (entity && entity->components.find(arg.id()) != entity->components.end()); }(args), ...);
      ([&](auto &arg) { result &= (entity && entity->Has(arg.id())); }(args), ...);

      // On l'ajoute à notre list final
      if (result) {
        entities[idx] = entity;
        idx++;
      }
    }

    entities.resize(idx);
  }

  /**
   * @brief Supprime l'entité, contenu dans la Pool
   */
  void Free(Entity *object) {
    Pool<Entity> &a = GetObjects();
    a.free(object);
  }

  Pool<Transform> trans_pool;
  Pool<Velocity> velo_pool;
  Pool<Collider> coll_pool;
  Pool<Renderer> rend_pool;

private:
  Pool<Entity> entities; // All entities
};