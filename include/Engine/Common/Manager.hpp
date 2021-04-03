#pragma once

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Factory/ComponentFactory.hpp>
#include <Engine/Factory/EntityFactory.hpp>
#include <Engine/Factory/SystemFactory.hpp>

/**
 * @brief Le Manager est un Thread-safe Singleton qui permet de gérer les données du jeu
 */
class Manager {
public:
  /**
   * @brief Retourne une unique instance du Manager (double-check locking)
   */
  static Manager *GetInstance();

  /**
   * @brief Permet d'allouer un Component
   * cf. ComponentFactory
   */
  void AllocateComponent(const RTTI::type rtti, Entity entity) { compFact->Allocate(rtti, entity); }

  /**
   * @brief Permet de libérer un Component
   * cf. ComponentFactory
   */
  void FreeComponent(const RTTI::type rtti, Entity entity) { compFact->Free(rtti, entity); }

  /**
   * @brief Permet d'enregistrer un Component dans la ComponentFactory
   * cf. ComponentFactory
   */
  template <typename T> void RegisterComponent() { compFact->Register<T>(); }

  /**
   * @brief Permet de récupèrer le Component d'une Entity
   */
  template <typename T> T *GetComponent(Entity entity) { return compFact->Get<T>(entity); }

  /**
   * @brief Permet de construire une Entity, alloue tout les Component et retourne une Entity nous utilisée
   * @param args Liste des arguments, normalement RTTI de Component
   * @return Retourne la nouvelle Entity
   */
  template <typename... Args> Entity AllocateEntity(Args &&... args) {
    const Entity &id = entiFact->Allocate();

    ([&](auto &arg) { AllocateComponent(arg.id(), id); }(args), ...);

    return id;
  }

  /**
   * @brief Permet de libérer une Entity
   */
  void FreeEntity(const Entity &entity) {
    compFact->FreeEntity(entity);
    entiFact->Free(entity);
  }

  /**
   * @brief Permet de récupèrer une liste d'Entity possèdant tous certains Component
   * @param entities Réfèrence vers la liste d'Entity (d'un System), que l'on rempli
   * @param args Liste des arguments, normalement RTTI de Component
   */
  template <typename... Args> void GetObjectsWithTag(std::vector<Entity> &entities, Args &&... args) {
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

  /**
   * @brief Permet d'enregistrer un System dans la SystemFactory
   */
  template <typename T> void RegisterSystem() { systFact->Register<T>(); }

  /**
   * @brief Permet d'update les System
   */
  void UpdateSystem(double deltaTime) { systFact->Update(deltaTime); }

private:
  /**
   * @brief Initalise le Manager en créant une ComponentFactory et une EntityFactory
   */
  Manager() {
    compFact = std::make_unique<ComponentFactory>();
    entiFact = std::make_unique<EntityFactory>();
    systFact = std::make_unique<SystemFactory>();
  }

  std::unique_ptr<ComponentFactory> compFact;
  std::unique_ptr<EntityFactory> entiFact;
  std::unique_ptr<SystemFactory> systFact;

  static std::atomic<Manager *> s_instance;
  static std::mutex s_mutex;
};
