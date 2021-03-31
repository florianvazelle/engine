#include <Engine/Game.hpp>

#include <iostream>
#include <thread>

#include <Engine/Common/ComponentFactory.hpp>
#include <Engine/Common/EntityFactory.hpp>
#include <Engine/Common/EntityManager.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

std::map<RTTI::type, ComponentFactory::AllocFree> ComponentFactory::Registry;

#define REGISTER_FACTORY(klass, pool)                                                                       \
  ComponentFactory::Register(klass::rtti, std::make_pair([obdb](void) -> Component* { return pool.alloc(); }, \
                                                       [obdb](Component* c) { pool.free((klass*)c); }));

Game::Game(std::shared_ptr<Scene> scene)
    : scene(scene), context(std::make_shared<Clock>(), std::make_shared<Input>(), std::make_shared<Engine>()) {
  // On enregistre tout les Components
  EntityFactory* obdb = EntityManager::GetInstance();

  REGISTER_FACTORY(Transform, obdb->trans_pool)
  REGISTER_FACTORY(Velocity, obdb->velo_pool)
  REGISTER_FACTORY(Collider, obdb->coll_pool)
  REGISTER_FACTORY(Renderer, obdb->rend_pool)
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

  scene->destroy();
}