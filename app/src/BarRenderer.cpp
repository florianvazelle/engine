#include <BarRenderer.hpp>

void BarRenderer::render(const Entity& entity) {
  LOG(LOG_INFO, "[BarRenderer]");

  Context* context = Context::GetInstance();
  Registry* registry = Registry::GetInstance();

  Transform* trans = registry->GetComponent<Transform>(entity);
  float4 size = trans->size();

  // First we set the rectangle fill colour to that of the spritecomponents.
  SDL_SetRenderDrawColor(context->window()->renderer(), 255.f, 255.f, 255.f,
                         255.f);

  // Then we create the actual rectangle.
  const SDL_Rect draw_rect = {
      static_cast<int>(trans->x()),
      static_cast<int>(trans->y()),
      static_cast<int>(size.x),
      static_cast<int>(size.y),
  };

  // Now the rectangle gets renderered with the appropriate colours and position
  // data to the window.
  SDL_RenderFillRect(context->window()->renderer(), &draw_rect);
}