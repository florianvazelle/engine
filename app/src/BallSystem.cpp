#include <unistd.h>

#include <BallSystem.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Common/Random.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>
#include <PongScene.hpp>

RTTI_DEFINITION(BallSystem, ISystem)

void BallSystem::update() const {
  LOG(LOG_INFO, "--- Ball Update ---");

  // Get the Manager
  Manager* man = Manager::GetInstance();
  // Get all Entity with Transform and Velocity Component
  man->GetObjectsWithTag(man->entitiesQuery, Transform::rtti, Velocity::rtti);

  assert(man->entitiesQuery.size() != 0);

  Entity e = man->entitiesQuery[0];

  // Update the Transform with Velocity
  Transform* t = man->GetComponent<Transform>(e);
  Velocity* v = man->GetComponent<Velocity>(e);

  // Allow the ball to move based on a fixed-timestep loop.
  Context* context = Context::GetInstance();

  t->translate({
      v->direction.x * context->clock()->deltaTime(),
      v->direction.y * context->clock()->deltaTime(),
      v->direction.z * context->clock()->deltaTime(),
      1,
  });

  // Ensure ball can be reset.
  if (t->x() < 0.f) {
    // Ball passed the player paddle, reset it.
    t->identity();
    t->translate({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 0.f});

    v->direction = float4{random(-1, 1), random(-1, 1), 0.f, 1.f};
  } else if (t->x() > (WINDOW_WIDTH - 16.f)) {  // screen width - sprite width
    // Ball passed the ai paddle, reset it.
    t->identity();
    t->translate({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 0.f});

    v->direction = float4{random(-1, 1), random(-1, 1), 0.f, 1.f};
  }

  // Lock to screen.
  if (t->y() < 0.f || t->y() > (WINDOW_HEIGHT - 16.f)) {
    // Reverse ball, "bouncing" it.
    v->direction.y *= -1.f;
  }
}