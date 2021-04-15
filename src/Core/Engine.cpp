#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Core/Context.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

void Engine::FixedUpdate() const {
  LOG(LOG_INFO, "[Engine] Update!");

  // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl operates on milliseconds
  // not nanoseconds.
  const constexpr float dt = 1000.0f / 60.0f;

  Context* context = Context::GetInstance();
  Manager* man = Manager::GetInstance();

  // This is a fixed-step gameloop
  while (context->clock()->deltaTime() >= dt) {
    man->UpdateSystem();
    context->clock()->Increment(dt);
  }
}

void Engine::Render() const {
  LOG(LOG_INFO, "[Engine] Render!");

  Manager* man = Manager::GetInstance();
  man->RenderSystem();
}
