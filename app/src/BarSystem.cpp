#include <BarSystem.hpp>
#include <PongScene.hpp>

void BarSystem::onKeyDown(KeyDown* keyDown) {
  switch (keyDown->key()) {
    case SDLK_z:
      player1_movement = BarSystem::MoveDirection::NORTH;
      break;

    case SDLK_s:
      player1_movement = BarSystem::MoveDirection::SOUTH;
      break;

    case SDLK_i:
      player2_movement = BarSystem::MoveDirection::NORTH;
      break;

    case SDLK_k:
      player2_movement = BarSystem::MoveDirection::SOUTH;
      break;
  }
}

void BarSystem::onKeyUp(KeyUp* keyUp) {
  if (keyUp->key() == SDLK_z || keyUp->key() == SDLK_s) {
    player1_movement = BarSystem::MoveDirection::STOPPED;
  }

  if (keyUp->key() == SDLK_i || keyUp->key() == SDLK_k) {
    player2_movement = BarSystem::MoveDirection::STOPPED;
  }
}

float4 BarSystem::computeDirection(const BarSystem::MoveDirection& movement,
                                   float& y) const {
  const Context* const context = Context::GetInstance();

  float4 dir = {0.f, 0.f, 0.f, 1.f};

  if (movement == BarSystem::MoveDirection::NORTH) {
    dir.y -= 0.0015f * context->clock()->deltaTime();
  } else if (movement == BarSystem::MoveDirection::SOUTH) {
    dir.y += 0.0015f * context->clock()->deltaTime();
  }

  if (y + dir.y < 0.0f) {
    y = 0.f;
    dir.y = 0.f;
  } else if (y + dir.y > (WINDOW_HEIGHT - 96.0f)) {
    y = (WINDOW_HEIGHT - 96.0f);
    dir.y = 0.f;
  }

  return dir;
}

void BarSystem::update() const {
  LOG(LOG_INFO, "--- Bar Update ---");

  Registry* registry = Registry::GetInstance();

  registry->GetEntitiesWithTags(registry->entitiesQuery, RectRenderer::rtti);

  // player 1
  {
    Entity e = registry->entitiesQuery[0];

    Transform* t = registry->GetComponent<Transform>(e);

    float4 dir = computeDirection(player1_movement, t->y());
    t->translate(dir);
  }

  // player 2
  {
    Entity e = registry->entitiesQuery[1];

    Transform* t = registry->GetComponent<Transform>(e);

    float4 dir = computeDirection(player2_movement, t->y());
    t->translate(dir);
  }
}