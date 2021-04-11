#include <BallSystem.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Transform.hpp>
#include <PongScene.hpp>
#include <Velocity.hpp>

RTTI_DEFINITION(BallSystem, ISystem)

void BallSystem::update(Context& context) {
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

  t->translate(v->direction * (context.deltaTime() / 2.0f));

  // Ensure ball can be reset.
  if (t->x() < 0.f) {
    // Ball passed the player paddle, reset it.
    t->identity();
    t->translate({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 0.f});

    v->direction = float4{-1.f, 0.75f, 0.f, 1.f};
  } else if (t->x() > (WINDOW_WIDTH - 16.f)) { // screen width - sprite width
    // Ball passed the ai paddle, reset it.
    t->identity();
    t->translate({WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 0.f, 0.f});

    v->direction = float4{-1.f, 0.75f, 0.f, 1.f};
  }

  // Lock to screen.
  if (t->y() < 0.f) {
    // Reverse ball, "bouncing" it.
    v->direction *= -1.f;
  } else if (t->y() > (WINDOW_HEIGHT - 16.f)) { // screen height - sprite height
    // Reverse ball, "bouncing" it.
    v->direction *= -1.f;
  }
}