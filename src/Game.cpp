#include <Engine/Game.hpp>

#include <iostream>
#include <thread>
#include "spdlog/spdlog.h"

Game::Game(std::shared_ptr<Scene> scene)
    : scene(scene), context(std::make_shared<Clock>(), std::make_shared<Input>(), std::make_shared<Engine>()) {}

void Game::preload() {
  /*  */
  scene->preload();
  /*  */
}

void Game::update() {
  context.c()->Update();
  context.i()->Update();
  context.e()->Update(context);
}

void Game::run() {
  try {
    preload();

    scene->create();

    bool needToQuit = false;

    // Main Loop
    while (!needToQuit) {
      spdlog::info("[Game] New frame!");

      update();

      // emule un delai de traitement (une synchro verticale par ex.)
      std::this_thread::sleep_for(std::chrono::milliseconds(10));  // TODO : on peut le supprimer par la suite

      // On regarde si l'utilisateur veut quitter le programme
      needToQuit = context.i()->QuitButtonIsPressed();
    }

  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}