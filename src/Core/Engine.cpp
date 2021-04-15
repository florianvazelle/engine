#include <Engine/Common/Registry.hpp>
#include <Engine/Core/Context.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>
#include <Engine/Util/Log.hpp>

void Engine::FixedUpdate() const {
  LOG(LOG_INFO, "[Engine] Update!");

  // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl operates on milliseconds
  // not nanoseconds.
  const constexpr double dt = 1000.0 / 60.0;

  Context* context = Context::GetInstance();
  Registry* registry = Registry::GetInstance();

  // This is a fixed-step gameloop
  while (context->clock()->deltaTime() >= dt) {
    registry->UpdateSystem();
    context->clock()->Increment(dt);
  }
}

void Engine::Render() const {
  LOG(LOG_INFO, "[Engine] Render!");

  Registry* registry = Registry::GetInstance();
  registry->RenderSystem();
}
