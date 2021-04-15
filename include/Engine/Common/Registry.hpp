#pragma once

#include <Engine/Common/RTTI.hpp>
#include <Engine/Common/Singleton.hpp>
#include <Engine/Component/IRenderer.hpp>
#include <Engine/Factory/ComponentFactory.hpp>
#include <Engine/Factory/EntityFactory.hpp>
#include <Engine/Factory/SystemFactory.hpp>
#include <map>
#include <vector>

/**
 * @brief Le Registry permet de gérer les données du jeu
 */
class Registry : public Singleton<Registry> {
  // needs to be friend in order to
  // access the private constructor/destructor
  friend class Singleton<Registry>;

 public:
  /**
   * @brief Permet d'allouer un IComponent
   * cf. ComponentFactory
   */
  void AllocateComponent(const RTTI& rtti, const Entity& entity) {
    compFact->Allocate(rtti, entity);
  }

  /**
   * @brief Permet de libérer un IComponent
   * cf. ComponentFactory
   */
  void FreeComponent(const RTTI& rtti, const Entity& entity) { compFact->Free(rtti, entity); }

  /**
   * @brief Permet d'enregistrer un IComponent dans la ComponentFactory
   * cf. ComponentFactory
   */
  template <typename T>
  void RegisterComponent() {
    compFact->Register<T>();
  }

  /**
   * @brief Permet de récupèrer le IComponent d'une Entity
   */
  template <typename T>
  T* GetComponent(const Entity& entity) {
    return compFact->Get<T>(entity);
  }

  /**
   * @brief Permet de récupèrer une liste de IComponent, fils d'un IComponent parent,  d'une Entity
   */
  template <typename T>
  T* GetComponentWithParent(const Entity& entity) {
    return compFact->GetWithParent<T>(entity);
  }

  /**
   * @brief Permet de construire une Entity, alloue tout les IComponent et retourne une Entity nous
   * utilisée
   * @param args Liste des arguments, normalement RTTI de IComponent
   * @return Retourne la nouvelle Entity
   */
  template <typename... Args>
  Entity AllocateEntity(Args&&... args) {
    const Entity& id = entiFact->Allocate();

    // clang-format off
    ([&](auto &arg) { AllocateComponent(arg.id(), id); }(args), ...);
    // clang-format on

    return id;
  }

  /**
   * @brief Permet de libérer une Entity
   */
  void FreeEntity(const Entity& entity) {
    compFact->FreeEntity(entity);
    entiFact->Free(entity);
  }

  /**
   * @brief Permet de récupèrer une liste d'Entity possèdant tous certains IComponent
   * @param entities Réfèrence vers la liste d'Entity (d'un ISystem), que l'on rempli
   * @param args Liste des arguments, normalement RTTI de IComponent
   */
  template <typename... Args>
  void GetObjectsWithTag(std::vector<Entity>& entities, Args&&... args) const {
    int idx = 0;
    entities.resize(MAX_ENTITIES);

    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
      if (!entiFact->IsSet(entity)) continue;
      if (compFact->Has(entity, std::forward<Args>(args)...)) {
        entities[idx] = entity;
        idx++;
      }
    }

    entities.resize(idx);  // Normalement pas d'allocation car la taille max est déjà réservé
  }

  template <typename T>
  void GetObjectsWithParentTag(std::vector<Entity>& entities) const {
    int idx = 0;
    entities.resize(MAX_ENTITIES);

    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
      if (!entiFact->IsSet(entity)) continue;
      if (compFact->HasWithParent<T>(entity)) {
        entities[idx] = entity;
        idx++;
      }
    }

    entities.resize(idx);  // Normalement pas d'allocation car la taille max est déjà réservé
  }

  /**
   * @brief Permet d'enregistrer un ISystem dans la SystemFactory
   */
  template <typename T>
  void RegisterSystem() {
    systFact->Register<T>();
  }

  /**
   * @brief Permet d'update les ISystem
   */
  void UpdateSystem() { systFact->Update(); }
  void RenderSystem() { systFact->Render(); }

  const size_t numThreads;
  ThreadPool threadPool;
  std::vector<Entity> entitiesQuery;
  std::vector<std::future<void>> results;

 private:
  /**
   * @brief Initalise le Registry en créant une ComponentFactory et une EntityFactory
   */
  Registry()
      : numThreads(std::thread::hardware_concurrency()),
        threadPool(numThreads),
        entitiesQuery(MAX_ENTITIES),
        results(MAX_ENTITIES) {
    compFact = std::make_unique<ComponentFactory>();
    entiFact = std::make_unique<EntityFactory>();
    systFact = std::make_unique<SystemFactory>();
  }
  ~Registry() {}

  std::unique_ptr<ComponentFactory> compFact;
  std::unique_ptr<EntityFactory> entiFact;
  std::unique_ptr<SystemFactory> systFact;
};