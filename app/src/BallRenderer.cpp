#include <BallRenderer.hpp>
#include <Engine/Common/Registry.hpp>

RTTI_DEFINITION(BallRenderer, IRenderer)

void BallRenderer::render(const Entity& entity) {
  LOG(LOG_INFO, "[BallRenderer]");
  Registry* registry = Registry::GetInstance();

  Transform* trans = registry->GetComponent<Transform>(entity);

  auto x = static_cast<Sint16>(trans->x());
  auto y = static_cast<Sint16>(trans->y());

  // We use SDL2_gfx to make drawing circles easier.
  Context* context = Context::GetInstance();
  filledCircleRGBA(context->window()->renderer(), x, y, 8, 255.f, 255.f, 255.f, 255.f);
}