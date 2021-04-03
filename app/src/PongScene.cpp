#include <PongScene.hpp>

#include <iostream>

#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>

#include <BallSystem.hpp>
#include <Velocity.hpp>

void PongScene::preload() {
  /**
   * @todo Load texture or 3D model here
   */

  Manager* man = Manager::GetInstance();

  // You need to register all custom Component and System
  man->RegisterComponent<Velocity>();
  man->RegisterSystem<BallSystem>();
}

void PongScene::create() {
  Manager* man = Manager::GetInstance();

  // You can create Entity with Component
  Entity test = man->AllocateEntity();
  player1     = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
  player2     = man->AllocateEntity(Transform::rtti, Collider::rtti, Renderer::rtti);
  ball        = man->AllocateEntity(Transform::rtti, Velocity::rtti);

  // std::cout << "test=" << test << "\n";
  // std::cout << "player1=" << player1 << "\n";
  // std::cout << "player2=" << player2 << "\n";
  // std::cout << "ball=" << ball << "\n";

  // man->FreeEntity(test);
  // man->FreeEntity(player1);
}