#include <BallRenderer.hpp>
#include <Engine/Common/Manager.hpp>

RTTI_DEFINITION(BallRenderer, IRenderer)

void BallRenderer::render(const Context& context, const Entity& entity) {
  LOG(LOG_INFO, "[BallRenderer]");
  Manager* man = Manager::GetInstance();

  Transform* trans = man->GetComponent<Transform>(entity);

  auto x = static_cast<Sint16>(trans->x());
  auto y = static_cast<Sint16>(trans->y());

  // We use SDL2_gfx to make drawing circles easier.
  filledCircleRGBA(context.window()->renderer(), x, y, 8, 255.f, 255.f, 255.f, 255.f);
}