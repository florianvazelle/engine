#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/IComponent.hpp>
#include <Engine/Component/IRenderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Factory/ComponentFactory.hpp>
#include <Engine/Factory/EntityFactory.hpp>
#include <Engine/Game.hpp>
#include <iostream>
#include <thread>

Game::Game(std::string title, const int w, const int h, std::uint32_t flags) : context() {
  // Setup SDL2 and stuff.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    throw_sdl2_exception("Failed to init SDL2.");
  }

  context.window()->create(title, w, h, flags);
}

Game::~Game() noexcept { SDL_Quit(); }

void Game::run(const std::shared_ptr<Scene>& scene) {
  try {
    scene->preload();

    // On enregistre tout les IComponent et tout les ISystem
    REGISTER_COMPONENTS
    REGISTER_SYSTEMS

    scene->create();

    // Main Loop
    while (context.window()->is_open()) {
      LOG(LOG_INFO, "~~~ New frame!");
      int start = SDL_GetTicks();

      context.clock()->Update();          // Clock
      context.input()->Update();          // Input
      context.engine()->Update(context);  // Engine

      // Limit the framerate
      int time = SDL_GetTicks() - start;
      if (time < 0) continue;  // if time is negative, the time probably overflew, so continue asap

      int sleepTime = 166 - time;
      if (sleepTime > 0) {
        SDL_Delay(sleepTime);
      }
    }

  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}