#pragma once

#include <memory>

#include <Engine/Common/Manager.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

// All Engine's System
#define SYSTEMS LogicalSystem, PhysicalSystem, RendererSystem

// Register a System
#define REGISTER_SYSTEM(klass) Manager::GetInstance()->RegisterSystem<klass>();

// Register all System
#define REGISTER_SYSTEMS MAP(REGISTER_SYSTEM, SYSTEMS)

class SystemFactory {
public:
  template <typename T> void Register() {
    const RTTI::type& id = T::rtti.id();

    if (systems.find(id) == systems.end()) {
      systems.insert({id, std::make_shared<T>()});
    }
  }

  void Update(double deltaTime) {
    for (auto const& x : systems) {
      x.second->update(deltaTime);
    }
  }

private:
  std::map<const RTTI::type, std::shared_ptr<System>> systems{};
};