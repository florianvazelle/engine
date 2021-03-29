#include <Engine/Game.hpp>

#include <iostream>

#include <Engine/System/LogicalSystem.hpp>
#include <Engine/System/PhysicalSystem.hpp>
#include <Engine/System/RendererSystem.hpp>

Game::Game(std::shared_ptr<Scene> scene) : scene(scene), systems(3) {
  systems[0] = std::make_shared<LogicalSystem>();
  systems[1] = std::make_shared<PhysicalSystem>();
  systems[2] = std::make_shared<RendererSystem>();
}

void Game::preload() {
  /*  */
  scene->preload();
  /*  */
}

void Game::run() {
  try {
    preload();

    // Main Loop
    while (1) {
      // TODO : compute deltaTime
      double deltaTime = 0;

      /*  */
      scene->update(deltaTime);
      /*  */

      for (std::shared_ptr<System> system : systems) {
        system->update(deltaTime);
      }
    }

  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}