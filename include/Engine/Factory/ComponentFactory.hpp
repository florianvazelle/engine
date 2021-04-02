#pragma once

#include <map>
#include <memory>
#include <string>

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/RTTI.hpp>
#include <Engine/Common/map.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>
#include <Engine/Pool/Pool.hpp>

#define REGISTER_COMPONENT(klass) Manager::GetInstance()->RegisterComponent<klass>();

#define ALLOC_COMPONENT(klass) \
  if (rtti == klass::rtti.id()) GetComponentPool<klass>()->alloc_with_id(entity);

#define FREE_COMPONENT(klass) \
  if (rtti == klass::rtti.id()) GetComponentPool<klass>()->free_with_id(entity);

#define HAS_COMPONENT(klass) \
  if (rtti == klass::rtti.id()) result &= (Get<klass>(entity) != nullptr);

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

    componentArrays.insert({typeName, std::make_shared<Pool<T>>(MAX_ENTITIES)});
  }

  /**
   * @brief Permet de récupèrer le Component d'une Entity
   * @param entity L'Entity qui possède le Component que l'on veut récupèrer
   * @return Le pointeur vers le Component de l'Entity, si il n'existe pas, retourne nullptr
   */
  template <typename T> T* Get(const Entity& entity) {
    const RTTI::type& typeName = T::rtti.id();

    Pool<T>* pool                         = GetComponentPool<T>().get();
    typename Pool<T>::PoolItem* pool_item = pool->at(entity);

    return (!pool->in_free_list(pool_item)) ? pool_item->get_storage() : nullptr;
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
    ([&](auto& arg) {
      const RTTI::type& rtti = arg.id();
      MAP(HAS_COMPONENT, Transform, Velocity, Collider, Renderer)
    } (args), ...);
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
  template <typename T> std::shared_ptr<Pool<T>> GetComponentPool() {
    const RTTI::type& typeName = T::rtti.id();
    assert(componentArrays.find(typeName) != componentArrays.end() && "Component not registered before use.");

    return std::static_pointer_cast<Pool<T>>(componentArrays[typeName]);
  }
};