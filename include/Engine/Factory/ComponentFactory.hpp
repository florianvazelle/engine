#pragma once

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/Macro.hpp>
#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/IComponent.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Factory/EntityFactory.hpp>
#include <Engine/Pool/ComponentArray.hpp>
#include <map>
#include <memory>
#include <string>

// All Engine's IComponent
#define COMPONENTS Transform, Collider

// Register a IComponent
#define REGISTER_COMPONENT(klass) Manager::GetInstance()->RegisterComponent<klass>();

// Register all IComponent
#define REGISTER_COMPONENTS MAP(REGISTER_COMPONENT, COMPONENTS)

/**
 * @brief Permet de gérer l'allocation/libération des IComponent
 */
class ComponentFactory {
 public:
  ComponentFactory();

  /**
   * @brief On alloue un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Allocate(const RTTI& rtti, const Entity& entity);

  /**
   * @brief On libère un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Free(const RTTI& rtti, const Entity& entity);

  /**
   * @brief On libère tout les IComponent associé a une Entity
   * @param entity Est l'Entity qui possède les IComponent à supprimés
   */
  void FreeEntity(const Entity& entity);

  /**
   * @brief On enregistre le IComponent est on crée une Pool associé
   */
  template <typename T>
  void Register() {
    const RTTI& typeName = T::rtti;
    assert(componentArrays.find(typeName) == componentArrays.end() &&
           "Registering component type more than once.");

    componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
  }

  /**
   * @brief Permet de récupèrer le IComponent d'une Entity
   * @param entity L'Entity qui possède le IComponent que l'on veut récupèrer
   * @return Le pointeur vers le IComponent de l'Entity, si il n'existe pas, retourne nullptr
   */
  template <typename T>
  T* Get(const Entity& entity) const {
    auto pool = GetComponentPool<T>().get();
    return (T*)pool->Get(entity);
  }

  /**
   * @brief Permet de récupèrer le IComponent, fils d'un IComponent parent
   * @param entity L'Entity qui possède le IComponent que l'on veut récupèrer
   * @return Le pointeur vers le IComponent de l'Entity, si il n'existe pas, retourne nullptr
   */
  template <typename T>
  T* GetWithParent(const Entity& entity) const {
    for (const auto& c : componentArrays) {
      if (c.first.IsA(T::rtti)) {
        T* component = (T*)c.second->Get(entity);
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
    // clang-format off
    ([&](auto& arg) { result &= (componentArrays.at(arg.id())->Get(entity) != nullptr); } (args), ...);
    // clang-format on
    return result;
  }

  template <typename T>
  bool HasWithParent(const Entity& entity) const {
    for (const auto& c : componentArrays) {
      if (c.first.IsA(T::rtti)) {
        if (c.second->Get(entity) != nullptr) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  struct CompareMapRTTI {
    bool operator()(const RTTI& a, const RTTI& b) const { return a.id() < b.id(); }
  };

  std::map<RTTI, std::shared_ptr<IPool>, CompareMapRTTI>
      componentArrays;  // Map de l'id d'un IComponent vers une Pool de IComponent

  /**
   * @brief Permet d'obtenir pointeur de la Pool de type T
   * @return Le pointeur de la Pool T
   */
  template <typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentPool() const {
    const RTTI& typeName = T::rtti;
    assert(componentArrays.find(typeName) != componentArrays.end() &&
           "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(componentArrays.at(typeName));
  }
};