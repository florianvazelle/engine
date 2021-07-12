#pragma once

#include <cstdint>
#include <engine/ecs/ISystem.hpp>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

class LogicalSystem;
class PhysicalSystem;
class RendererSystem;

// All Engine's ISystem
#define SYSTEMS LogicalSystem, PhysicalSystem, RendererSystem

// Register a ISystem
#define REGISTER_SYSTEM(klass) Registry::GetInstance()->RegisterSystem<klass>();

// Register all ISystem
#define REGISTER_SYSTEMS MAP(REGISTER_SYSTEM, SYSTEMS)

class SystemFactory {
 public:
  SystemFactory() : engineSystems(3) {}

  template <typename T>
  T* Register() {
    if constexpr (std::is_same_v<T, LogicalSystem>) {
      engineSystems[0] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[0].get());
    } else if constexpr (std::is_same_v<T, PhysicalSystem>) {
      engineSystems[1] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[1].get());
    } else if constexpr (std::is_same_v<T, RendererSystem>) {
      engineSystems[2] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[2].get());
    } else {
      const RTTI& id = T::rtti;

      if (systems.find(id) == systems.end()) {
        systems.insert({id, std::make_shared<T>()});
      }

      return reinterpret_cast<T*>(systems[id].get());
    }
    return nullptr;
  }

  void Update() {
    // On update d'abord les ISystem rajoutés
    for (auto const& x : systems) {
      x.second->update();
    }

    // Puis ensuite les ISystem de l'Engine
    engineSystems[0]->update();
    engineSystems[1]->update();
    // systems[RendererSystem::rtti]->update();

    // TODO : faire un système de dépendance entre les systèmes pour pouvoir
    // choisir l'ordre
  }

  void Render() { engineSystems[2]->update(); }

 private:
  std::map<const RTTI, std::shared_ptr<ISystem>> systems{};
  std::vector<std::shared_ptr<ISystem>> engineSystems;
};