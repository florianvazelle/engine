#include <PongScene.hpp>

#include <iostream>

#include <Engine/Common/EntityManager.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

void PongScene::preload() {}

void PongScene::create() {
  EntityFactory* obdb = EntityManager::GetInstance();
  Entity* test        = obdb->Allocate();
  player1             = obdb->Allocate(Transform::rtti, Collider::rtti, Renderer::rtti);
  player2             = obdb->Allocate(Transform::rtti, Collider::rtti, Renderer::rtti);
  ball                = obdb->Allocate(Transform::rtti, Velocity::rtti);
  std::cout << "test=" << test << "\n";
  std::cout << "player1=" << player1 << "\n";
  std::cout << "player2=" << player2 << "\n";
  std::cout << "ball=" << ball << "\n";
  // obdb->Free(test);
  // obdb->Free(player1);
  // std::cout << "player1=" << player1 << "\n";
}

void PongScene::update(double deltaTime) { LOG("update!"); }

void PongScene::destroy() {
  EntityFactory* obdb = EntityManager::GetInstance();
  // obdb->Free(ball);
  // obdb->Free(player2);
  obdb->Free(player1);
}