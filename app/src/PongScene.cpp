#include <BallRenderer.hpp>
#include <BallSystem.hpp>
#include <BarRenderer.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/IRenderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <PongScene.hpp>
#include <Velocity.hpp>
#include <iostream>

void PongScene::preload() {
  /**
   * @todo Load texture or 3D model here
   */
}

void PongScene::create() {
  Manager* man = Manager::GetInstance();

  // You need to register all custom IComponent and ISystem
  man->RegisterComponent<Velocity>();
  man->RegisterComponent<BallRenderer>();
  man->RegisterComponent<BarRenderer>();
  man->RegisterSystem<BallSystem>();

  // You can create Entity with IComponent
  Entity e1 = man->AllocateEntity(Transform::rtti, Collider::rtti, BarRenderer::rtti);
  Entity e2 = man->AllocateEntity(Transform::rtti, Collider::rtti, BarRenderer::rtti);
  Entity ball = man->AllocateEntity(Transform::rtti, Velocity::rtti, BallRenderer::rtti);

  Transform* t1 = man->GetComponent<Transform>(e1);
  t1->translate(float4{20, 20, 0, 1});

  Transform* t2 = man->GetComponent<Transform>(e2);
  t2->translate(float4{20, 60, 0, 1});

  std::cout << "player1=" << e1 << std::endl;
  std::cout << "player2=" << e2 << std::endl;
  std::cout << "ball=" << ball << std::endl;
}