#include <PongScene.hpp>

#include <iostream>

#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Velocity.hpp>

void PongScene::preload() {}

void PongScene::create() {
  entitiesQuery.reserve(MAX_ENTITIES);

  Manager* man = Manager::GetInstance();
  Entity test  = man->AllocateEntity();
  player1      = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
  player2      = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
  ball         = man->AllocateEntity(Transform::rtti, Velocity::rtti);

  std::cout << "test=" << test << "\n";
  std::cout << "player1=" << player1 << "\n";
  std::cout << "player2=" << player2 << "\n";
  std::cout << "ball=" << ball << "\n";

  man->FreeEntity(test);
  man->FreeEntity(player1);
}

void PongScene::update(double deltaTime) {
  Manager* man = Manager::GetInstance();

  man->GetObjectsWithTag(entitiesQuery, Transform::rtti, Velocity::rtti);
}