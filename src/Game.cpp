#include <Engine/Game.hpp>

#include <iostream>
#include <thread>

#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>
#include <Engine/Factory/ComponentFactory.hpp>
#include <Engine/Factory/EntityFactory.hpp>

Game::Game(std::shared_ptr<IScene> scene)
    : scene(scene), context(std::make_shared<Clock>(), std::make_shared<Input>(), std::make_shared<Engine>()) {
  // On enregistre tout les Components
  MAP(REGISTER_COMPONENT, Transform, Velocity, Collider, Renderer)
}

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
      LOG("New frame!");

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