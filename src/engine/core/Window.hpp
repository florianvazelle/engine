#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <engine/meta/Log.hpp>
#include <string>

class Window {
 public:
  Window() : m_is_open{true}, m_window{nullptr}, m_renderer{nullptr} {}

  ~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
  }

  void create(std::string title, const int w, const int h,
              std::uint32_t flags) {
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (!m_window) {
      throw_sdl2_exception("Window failed to be created.");
    }

    m_renderer = SDL_CreateRenderer(
        m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
      throw_sdl2_exception("Renderer failed to be created.");
    }
  }

  void close() noexcept { m_is_open = false; }

  bool is_open() const noexcept { return m_is_open; }
  SDL_Renderer* renderer() const noexcept { return m_renderer; }

  SDL_Event m_event;

 private:
  bool m_is_open;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};