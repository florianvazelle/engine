#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <string>

class Window {
 public:
  Window();
  ~Window();

  void create(std::string title, const int w, const int h, std::uint32_t flags);
  void close() noexcept;

  bool is_open() const noexcept;
  SDL_Renderer* renderer() const noexcept;

  SDL_Event m_event;

 private:
  bool m_is_open;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};