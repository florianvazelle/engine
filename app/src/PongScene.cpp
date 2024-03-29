#include <BallSystem.hpp>
#include <BarSystem.hpp>
#include <PongScene.hpp>

void PongScene::preload() {
  /**
   * @todo Load texture or 3D model here
   */
}

void PongScene::create() {
  Registry* registry = Registry::GetInstance();
  Dispatcher* dispatcher = Dispatcher::GetInstance();

  // You can create Entity with IComponent
  Entity e1 = registry->AllocateEntity(Transform::rtti, RectCollider::rtti, RectRenderer::rtti);
  Entity e2 = registry->AllocateEntity(Transform::rtti, RectCollider::rtti, RectRenderer::rtti);
  Entity ball = registry->AllocateEntity(Transform::rtti, RectCollider::rtti, Velocity::rtti,
                                         CircleRenderer::rtti);

  Transform* t1 = registry->GetComponent<Transform>(e1);
  t1->translate(float4{20.f, 20.f, 0.f, 1.f});
  t1->scale({12, 96, 1, 1});

  Transform* t2 = registry->GetComponent<Transform>(e2);
  t2->translate(float4{WINDOW_WIDTH - 30.f, 20.f, 0.f, 1.f});
  t2->scale({12, 96, 1, 1});

  Transform* t3 = registry->GetComponent<Transform>(ball);
  t3->translate(float4{WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 1.f});
  t3->scale({8, 8, 1, 1});

  Velocity* v = registry->GetComponent<Velocity>(ball);
  v->direction = float4{random(-0.3, 0.25), random(-0.3, 0.25), 0.f, 1.f};  // intial velocity

  // You can assign event with system method
  BarSystem* barSystem = registry->RegisterSystem<BarSystem>();
  BallSystem* ballSystem = registry->RegisterSystem<BallSystem>();

  dispatcher->RegisterAction<BarSystem, KeyDown>(barSystem, &BarSystem::onKeyDown);
  dispatcher->RegisterAction<BarSystem, KeyUp>(barSystem, &BarSystem::onKeyUp);

  dispatcher->RegisterAction<BallSystem, Collide>(ballSystem, &BallSystem::onCollide);
}