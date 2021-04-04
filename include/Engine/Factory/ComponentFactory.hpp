#pragma once

#include <map>
#include <memory>
#include <string>

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/Macro.hpp>
#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Pool/ComponentArray.hpp>

// All Engine's Component
#define COMPONENTS Transform, Collider, Renderer

// Register a Component
#define REGISTER_COMPONENT(klass) Manager::GetInstance()->RegisterComponent<klass>();

// Register all Component
#define REGISTER_COMPONENTS MAP(REGISTER_COMPONENT, COMPONENTS)

/**
 * @brief Permet de gérer l'allocation/libération des Component
 */
class ComponentFactory {
public:
  ComponentFactory();

  /**
   * @brief On alloue un Component associé a une Entity
   * @param rtti Est l'identifiant du Component à supprimer
   * @param entity Est l'Entity qui possède le Component à supprimé
   */
  void Allocate(const RTTI::type& rtti, const Entity& entity);

  /**
   * @brief On libère un Component associé a une Entity
   * @param rtti Est l'identifiant du Component à supprimer
   * @param entity Est l'Entity qui possède le Component à supprimé
   */
  void Free(const RTTI::type& rtti, const Entity& entity);

  /**
   * @brief On libère tout les Component associé a une Entity
   * @param entity Est l'Entity qui possède les Component à supprimés
   */
  void FreeEntity(const Entity& entity);

  /**
   * @brief On enregistre le Component est on crée une Pool associé
   */
  template <typename T> void Register() {
    const RTTI::type& typeName = T::rtti.id();
    assert(componentArrays.find(typeName) == componentArrays.end() && "Registering component type more than once.");

    componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
  }

  /**
   * @brief Permet de récupèrer le Component d'une Entity
   * @param entity L'Entity qui possède le Component que l'on veut récupèrer
   * @return Le pointeur vers le Component de l'Entity, si il n'existe pas, retourne nullptr
   */
  template <typename T> T* Get(const Entity& entity) {
    auto pool = GetComponentPool<T>().get();
    return (T*)pool->Get(entity);
  }

  /**
   * @brief Permet de savoir si une Entity possède certains Component
   * @param entity L'Entity qui possède les Component
   * @param args Les différents RTTI des Component que l'on veut tester
   * @return Retourne vraie si l'entité possède tout les Component
   */
  template <typename... Args> bool Has(const Entity& entity, Args&&... args) {
    bool result = true;
    // clang-format off
    ([&](auto& arg) { result &= (componentArrays[arg.id()]->Get(entity) != nullptr); } (args), ...);
    // clang-format on
    return result;
  }

private:
  std::map<RTTI::type,
           std::shared_ptr<IPool>>
      componentArrays;  // Map de l'id d'un Component vers une Pool de Component

  /**
   * @brief Permet d'obtenir pointeur de la Pool de type T
   * @return Le pointeur de la Pool T
   */
  template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentPool() {
    const RTTI::type& typeName = T::rtti.id();
    assert(componentArrays.find(typeName) != componentArrays.end() && "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
  }
};