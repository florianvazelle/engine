#pragma once

#include <Engine/Common/Manager.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>
#include <memory>

// All Engine's ISystem
#define SYSTEMS LogicalSystem, PhysicalSystem, RendererSystem

// Register a ISystem
#define REGISTER_SYSTEM(klass) Manager::GetInstance()->RegisterSystem<klass>();

// Register all ISystem
#define REGISTER_SYSTEMS MAP(REGISTER_SYSTEM, SYSTEMS)

class SystemFactory {
 public:
  template <typename T>
  void Register() {
    const RTTI::type& id = T::rtti.id();

    if (systems.find(id) == systems.end()) {
      systems.insert({id, std::make_shared<T>()});
    }
  }

  void Update(const Context& context) {
    // On update d'abord les ISystem rajoutés
    for (auto const& x : systems) {
      if (x.first == LogicalSystem::rtti.id() || x.first == PhysicalSystem::rtti.id() ||
          x.first == RendererSystem::rtti.id())
        continue;
      x.second->update(context);
    }

    // Puis ensuite les ISystem de l'Engine
    systems[LogicalSystem::rtti.id()]->update(context);
    systems[PhysicalSystem::rtti.id()]->update(context);
    // systems[RendererSystem::rtti.id()]->update(context);

    // TODO : faire un système de dépendance entre les systèmes pour pouvoir choisir l'ordre
  }

  void Render(const Context& context) { systems[RendererSystem::rtti.id()]->update(context); }

 private:
  std::map<const RTTI::type, std::shared_ptr<ISystem>> systems{};
};