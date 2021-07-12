#pragma once

#include <engine/Game.hpp>
#include <engine/Scene.hpp>
#include <engine/component/IRenderer.hpp>
#include <engine/component/RectCollider.hpp>
#include <engine/component/Transform.hpp>
#include <engine/component/Velocity.hpp>
#include <engine/core/Clock.hpp>
#include <engine/core/Engine.hpp>
#include <engine/core/Input.hpp>
#include <engine/ecs/IComponent.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/factory/EntityFactory.hpp>
#include <engine/factory/Registry.hpp>
#include <engine/factory/SystemFactory.hpp>
#include <engine/meta/Log.hpp>
#include <engine/system/LogicalSystem.hpp>
#include <engine/system/PhysicalSystem.hpp>
#include <engine/system/RendererSystem.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

class Game {
 public:
  Game(std::string title, const int w, const int h, std::uint32_t flags) {
    // Setup SDL2 and stuff.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
      throw_sdl2_exception("Failed to init SDL2.");
    }

    Context* context = Context::GetInstance();
    context->window()->create(title, w, h, flags);
  }

  ~Game() noexcept { SDL_Quit(); }

  void run(const std::shared_ptr<Scene>& scene) {
    try {
      scene->preload();

      // On enregistre tout les IComponent et tout les ISystem
      REGISTER_COMPONENTS
      REGISTER_SYSTEMS

      scene->create();

      Context* context = Context::GetInstance();
      context->clock()->Initialize();

      int frameIndex = 0;
      while (context->window()->is_open()) {
        LOG(LOG_INFO, "[Game] frame # " << frameIndex);

        context->clock()->Update();
        context->input()->Update();

        context->engine()->FixedUpdate();
        context->engine()->Render();

        frameIndex++;
      }
    } catch (const std::exception& e) {
      LOG(LOG_ERROR, e.what());
    }
  }
};