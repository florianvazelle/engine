#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Core/Context.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

void Engine::FixedUpdate(const Context& context) const {
  LOG(LOG_INFO, "[Engine] Update!");

  context.clock()->FixedUpdate([context]() {
    Manager* man = Manager::GetInstance();
    man->UpdateSystem(context);
  });
}

void Engine::Render(const Context& context) const {
  LOG(LOG_INFO, "[Engine] Render!");

  Manager* man = Manager::GetInstance();
  man->RenderSystem(context);
}
