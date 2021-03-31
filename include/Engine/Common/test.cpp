#pragma once

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Pool/Pool.hpp>

#define MAX_ENTITIES 10

class EntityFactory {
public:
  EntityFactory() {}

  /**
   * @brief Ajoute d'une entité de type T, à la Pool d'entitée, du type T correspondant
   * @param args Liste d'argument pour initaliser une entité
   * @return Pointeur vers l'entité alloué
   */
  template <typename T, typename... Args> T *Allocate(Args &&... args) {
    Pool<Entity> &a = GetOrAlloc<T>();
    return reinterpret_cast<T *>(a.alloc(std::forward<Args>(args)...));
  }

  /**
   * @brief Si la Pool du type T existe on la retourne, sinon on la crée
   * @return Retourne une Pool d'entité de type T correspondant
   */
  template <typename T> Pool<Entity> &GetOrAlloc() {
    EntityCollection *&el = m_obdb[T::rtti.id()];

    if (!el) {
      // Crée une nouvelle Pool
      el              = new EntityCollection();
      Pool<Entity> &a = el->entities;
      return a;
    }

    return GetObjects<T>();
  }

  /**
   * @brief Permet de récupérer toutes les entitées alloué d'un type T
   * @return Retourne une Pool d'entité du type T correspondant
   * @throw Lève une exception si aucune Pool n'existe pour le type T correspondant
   */
  template <typename T> Pool<Entity> &GetObjects() {
    EntityCollection *&el = m_obdb[T::rtti.id()];

    // Si le pointeur est null, alors il n'y a jamais eu d'allocation pour ce type d'objet
    if (!el) {
      throw std::runtime_error("No pool allocation!");
    }

    Pool<Entity> &a = el->entities;
    return a;
  }

  template <typename... Args> void GetObjectsWithTag(std::vector<Entity *> &entities, Args &&... args) {
    // TODO: thread pool this function
    int idx = 0;

    // On parcours l'ensemble de nos Collections
    for (ObDB::iterator it = m_obdb.begin(); it != m_obdb.end(); ++it) {
      // Si c'est une EntityCollection d'entity
      // if (m_obdb->first.isA(Entity::rtti))
      LOG("m_obdb");
      {
        // On récupère la Pool correspondante
        Pool<Entity> &a = it->second->entities;

        // On parcours ensuite la Pool
        for (typename Pool<Entity>::iterator i = a.begin(); i != a.end(); ++i) {
          bool result = true;
          LOG("a");

          // On parcours l'ensemble des types
          (
              [&](auto &arg) {
                // Si ils sont contenu dans les components de l'entity
                LOG("arg " + arg.name() + " " + i->rtti.name() + " " + std::to_string(i->components.size()));
                Component *el = i->components[arg.id()];
                result        = result && (el != nullptr);
              }(args),
              ...);

          // On l'ajoute à notre list final
          if (result) {
            entities[idx] = i;
            idx++;
          }
        }
      }
    }
    LOG("exit");
    entities.resize(idx);
  }

  /**
   * @brief Supprime l'entité de type T, contenu dans la Pool du type T correspondant
   */
  template <typename T> void Free(T *object) {
    Pool<Entity> &a = GetObjects<T>();
    return a.free(object);
  }

  ~EntityFactory() {
    for (ObDB::iterator i = m_obdb.begin(); i != m_obdb.end(); ++i) delete i->second;
  }

private:
  EntityFactory(EntityFactory const &);
  EntityFactory &operator=(EntityFactory const &);

  struct EntityCollection {
    Pool<Entity> entities;
    EntityCollection() : entities(MAX_ENTITIES) {}
    EntityCollection(size_t arena_size) : entities(arena_size) {}
  };

  typedef std::map<RTTI::type, EntityCollection *> ObDB;
  ObDB m_obdb;
};

/*
    Example usage :

    #include <Engine/Common/EntityFactory.hpp>

    struct Foo {
      Foo() : name("Generic Foo") {}
      char const *name;
    };

    struct Bar {
      std::string name;
    };

    int main() {
      EntityFactory obdb;
      obdb.allocate<Foo>()->name = "My First Foo";
      obdb.allocate<Bar>()->name = "My First Bar";
      {
        Foo *f  = obdb.allocate<Foo>();
        f->name = "My Second Foo";
        Bar *b  = obdb.allocate<Bar>();
        b->name = "My Second Bar";
      }
      obdb.allocate<Foo>();
      obdb.allocate<Bar>();
      {
        std::cout << "Printing Foo Names\n";
        Pool<Foo> &foos = obdb.getObjects<Foo>();
        for (Pool<Foo>::iterator i = foos.begin(); i != foos.end(); ++i) std::cout << "   -> " << i->name << "\n";
      }
      {
        std::cout << "Printing Bar Names\n";
        Pool<Bar> &bars = obdb.getObjects<Bar>();
        for (Pool<Bar>::iterator i = bars.begin(); i != bars.end(); ++i) std::cout << "   -> " << i->name << "\n";
      }
    }
*/