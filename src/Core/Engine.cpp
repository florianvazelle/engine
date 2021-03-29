#include <Engine/Core/Context.hpp>
#include <Engine/Core/Engine.hpp>

#include "spdlog/spdlog.h"

#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

Engine::Engine() : systems(3) {
  systems[0] = std::make_shared<LogicalSystem>();
  systems[1] = std::make_shared<PhysicalSystem>();
  systems[2] = std::make_shared<RendererSystem>();
}

void Engine::Update(Context& context) {
  spdlog::info("[Engine] Update!");

  double elapsedTime = context.c()->elpsTime();

  // tout lag est maximise 100 ms (1/10 de seconde)
  // cela permet d'eviter de faire sauter le moteur en cas de breakpoint ou
  // lag enorme alternativement on peut appliquer une correction en
  // extrapolant a partir du temps ecoule
  if (elapsedTime > 0.10) elapsedTime = 0.10;

  float deltaTime = static_cast<float>(elapsedTime);

  for (std::shared_ptr<System> system : systems) {
    system->update(deltaTime);
  }
}
