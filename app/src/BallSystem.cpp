#include <BallSystem.hpp>
#include <PongScene.hpp>

void BallSystem::onCollide(Collide* collide) {
  Registry* registry = Registry::GetInstance();

  Velocity* v1 = registry->GetComponent<Velocity>(collide->entity1());
  if (v1 != nullptr) {
    v1->direction.x *= -1.f;
  }

  Velocity* v2 = registry->GetComponent<Velocity>(collide->entity2());
  if (v2 != nullptr) {
    v2->direction.x *= -1.f;
  }
}

void BallSystem::update() const {
  LOG(LOG_INFO, "--- Ball Update ---");

  // Get the Registry
  Registry* registry = Registry::GetInstance();
  // Get all Entity with Transform and Velocity Component
  registry->GetObjectsWithTag(registry->entitiesQuery, Transform::rtti,
                              Velocity::rtti);

  assert(registry->entitiesQuery.size() != 0);

  Entity e = registry->entitiesQuery[0];

  // Update the Transform with Velocity
  Transform* t = registry->GetComponent<Transform>(e);
  Velocity* v = registry->GetComponent<Velocity>(e);

  // Allow the ball to move based on a fixed-timestep loop.
  Context* context = Context::GetInstance();

  t->translate({
      v->direction.x * 0.15f * context->clock()->deltaTime(),
      v->direction.y * 0.15f * context->clock()->deltaTime(),
      v->direction.z * 0.15f * context->clock()->deltaTime(),
      1,
  });

  // Ensure ball can be reset.
  if (t->x() < 0.f || t->x() > (WINDOW_WIDTH - 16.f)) {
    // Ball passed the player paddle, reset it.
    t->identity();
    t->translate({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 1.f});
    t->scale({8, 8, 1, 1});

    v->direction = float4{random(-0.3, 0.25), random(-0.3, 0.25), 0.f, 1.f};
  }

  // Lock to screen.
  if (t->y() < 0.f || t->y() > (WINDOW_HEIGHT - 16.f)) {
    // Reverse ball, "bouncing" it.
    v->direction.y *= -1.f;
  }
}