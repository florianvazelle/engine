#include <BallRenderer.hpp>
#include <BallSystem.hpp>
#include <BarRenderer.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Common/Random.hpp>
#include <Engine/Component/ICollider.hpp>
#include <Engine/Component/IRenderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>
#include <PongScene.hpp>
#include <iostream>

void PongScene::preload() {
  /**
   * @todo Load texture or 3D model here
   */
}

void PongScene::create() {
  Manager* man = Manager::GetInstance();

  // You need to register all custom IComponent and ISystem
  man->RegisterComponent<BallRenderer>();
  man->RegisterComponent<BarRenderer>();
  man->RegisterSystem<BallSystem>();

  // You can create Entity with IComponent
  Entity e1 = man->AllocateEntity(Transform::rtti, RectCollider::rtti, BarRenderer::rtti);
  Entity e2 = man->AllocateEntity(Transform::rtti, RectCollider::rtti, BarRenderer::rtti);
  Entity ball = man->AllocateEntity(Transform::rtti, Velocity::rtti, BallRenderer::rtti);

  Transform* t1 = man->GetComponent<Transform>(e1);
  t1->translate(float4{20.f, 20.f, 0.f, 1.f});
  t1->scale({12, 96, 1, 1});

  Transform* t2 = man->GetComponent<Transform>(e2);
  t2->translate(float4{WINDOW_WIDTH - 30.f, 20.f, 0.f, 1.f});
  t2->scale({12, 96, 1, 1});

  Transform* t3 = man->GetComponent<Transform>(ball);
  t3->translate(float4{WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 1.f});
  t3->scale({8, 8, 1, 1});

  Velocity* v = man->GetComponent<Velocity>(ball);
  v->direction = float4{random(-1, 1), random(-1, 1), 0.f, 1.f};  // intial velocity
}