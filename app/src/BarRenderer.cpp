#include <BarRenderer.hpp>
#include <Engine/Common/Manager.hpp>

RTTI_DEFINITION(BarRenderer, IRenderer)

void BarRenderer::render(const Context& context, const Entity& entity) {
  LOG(LOG_INFO, "[BarRenderer]");

  Manager* man = Manager::GetInstance();

  Transform* trans = man->GetComponent<Transform>(entity);

  // First we set the rectangle fill colour to that of the spritecomponents.
  SDL_SetRenderDrawColor(context.window()->renderer(), 255.f, 255.f, 255.f, 255.f);

  // Then we create the actual rectangle.
  const SDL_Rect draw_rect = {static_cast<int>(trans->x()), static_cast<int>(trans->y()), 12, 96};

  // Now the rectangle gets renderered with the appropriate colours and position data to the window.
  SDL_RenderFillRect(context.window()->renderer(), &draw_rect);
}