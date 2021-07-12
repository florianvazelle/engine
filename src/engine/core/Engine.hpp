#pragma once

#include <engine/core/Context.hpp>
#include <engine/factory/ComponentFactory.hpp>
#include <engine/factory/EntityFactory.hpp>
#include <engine/factory/Registry.hpp>
#include <engine/factory/SystemFactory.hpp>
#include <engine/meta/Log.hpp>
#include <engine/system/LogicalSystem.hpp>
#include <engine/system/PhysicalSystem.hpp>
#include <engine/system/RendererSystem.hpp>
#include <memory>
#include <vector>

class Engine {
 public:
  void FixedUpdate() const {
    LOG(LOG_INFO, "[Engine] Update!");

    // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl
    // operates on milliseconds not nanoseconds.
    const constexpr double dt = 1000.0 / 60.0;

    Context* context = Context::GetInstance();
    Registry* registry = Registry::GetInstance();

    // This is a fixed-step gameloop
    while (context->clock()->deltaTime() >= dt) {
      registry->UpdateSystem();
      context->clock()->Increment(dt);
    }
  }

  void Render() const {
    LOG(LOG_INFO, "[Engine] Render!");

    Registry* registry = Registry::GetInstance();
    registry->RenderSystem();
  }
};