#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Core/Context.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

void Engine::Update(Context& context) {
  LOG(LOG_INFO, "[Engine] Update!");

  Manager* man = Manager::GetInstance();
  man->UpdateSystem(context);
}
