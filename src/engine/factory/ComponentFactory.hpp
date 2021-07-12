#pragma once

#include <engine/ecs/Entity.hpp>
#include <engine/ecs/IComponent.hpp>
#include <engine/meta/Macro.hpp>
#include <engine/meta/RTTI.hpp>
#include <engine/pool/ComponentArray.hpp>
#include <map>
#include <memory>
#include <string>

// All Engine's IComponent
#define COMPONENTS Transform, RectCollider, Velocity

// Register a IComponent
#define REGISTER_COMPONENT(klass) \
  Registry::GetInstance()->RegisterComponent<klass>();

// Register all IComponent
#define REGISTER_COMPONENTS MAP(REGISTER_COMPONENT, COMPONENTS)

/**
 * @brief Permet de gérer l'allocation/libération des IComponent
 */
class ComponentFactory {
 public:
  /**
   * @brief On alloue un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Allocate(const RTTI& rtti, const Entity& entity) {
    it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() &&
           "We cannot allocate a unknow Component.");
    it->second->Allocate(entity);
  }

  /**
   * @brief On libère un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Free(const RTTI& rtti, const Entity& entity) {
    it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() && "We cannot free a unknow Component.");
    it->second->Free(entity);
  }

  /**
   * @brief On libère tout les IComponent associé a une Entity
   * @param entity Est l'Entity qui possède les IComponent à supprimés
   */
  void FreeEntity(const Entity& entity) {
    for (auto const& x : componentArrays) {
      Free(x.first, entity);
    }
  }

  /**
   * @brief On enregistre le IComponent est on crée une Pool associé
   */
  template <typename T>
  void Register() {
    const RTTI& rtti = T::rtti;

    assert(componentArrays.find(rtti) == componentArrays.end() &&
           "Registering component type more than once.");

    componentArrays.insert({rtti, std::make_shared<ComponentArray<T>>()});
  }

  /**
   * @brief Permet de récupèrer le IComponent d'une Entity
   * @param entity L'Entity qui possède le IComponent que l'on veut récupèrer
   * @return Le pointeur vers le IComponent de l'Entity, si il n'existe pas,
   * retourne nullptr
   */
  template <typename T>
  T* Get(const Entity& entity) const {
    auto pool = GetComponentPool<T>().get();
    return reinterpret_cast<T*>(pool->Get(entity));
  }

  /**
   * @brief Permet de récupèrer le IComponent, fils d'un IComponent parent
   * @param entity L'Entity qui possède le IComponent que l'on veut récupèrer
   * @return Le pointeur vers le IComponent de l'Entity, si il n'existe pas,
   * retourne nullptr
   */
  template <typename T>
  T* GetWithParent(const Entity& entity) const {
    for (const auto& c : componentArrays) {
      if (T::IsA(c.first)) {
        T* component = reinterpret_cast<T*>(c.second->Get(entity));
        if (component != nullptr) {
          return component;
        }
      }
    }
    return nullptr;
  }

  /**
   * @brief Permet de savoir si une Entity possède certains IComponent
   * @param entity L'Entity qui possède les IComponent
   * @param args Les différents RTTI des IComponent que l'on veut tester
   * @return Retourne vraie si l'entité possède tout les IComponent
   */
  template <typename... Args>
  bool Has(const Entity& entity, Args&&... args) const {
    bool result = true;
    auto check_has = [&](auto& arg) {
      result &= (componentArrays.at(arg)->Get(entity) != nullptr);
    };
    (check_has(args), ...);
    return result;
  }

  template <typename T>
  bool HasWithParent(const Entity& entity) const {
    for (const auto& c : componentArrays) {
      if (T::IsA(c.first)) {
        if (c.second->Get(entity) != nullptr) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  using it_comp_t = std::map<RTTI, std::shared_ptr<IPool>>::iterator;
  using const_it_comp_t =
      std::map<RTTI, std::shared_ptr<IPool>>::const_iterator;

  std::map<RTTI, std::shared_ptr<IPool>>
      componentArrays;  // Map de l'id d'un IComponent vers une Pool de
                        // IComponent

  /**
   * @brief Permet d'obtenir pointeur de la Pool de type T
   * @return Le pointeur de la Pool T
   */
  template <typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentPool() const {
    const RTTI& rtti = T::rtti;

    const_it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(it->second);
  }
};