#pragma once

#include <SDL2/SDL_events.h>

#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>
#include <engine/event/KeyDown.hpp>
#include <engine/event/KeyUp.hpp>
#include <engine/event/Dispatcher.hpp>

class Context;

class Input {
 public:
  void Update() const {
    Dispatcher* dispatcher = Dispatcher::GetInstance();
    Context* context = Context::GetInstance();

    Window* window = context->window();
    SDL_Event& event = window->m_event;

    // Process all user and system events.
    while (SDL_PollEvent(&event) != 0) {
      // https://wiki.libsdl.org/SDL_Event
      switch (event.type) {
        case SDL_QUIT:
          window->close();
          break;

        case SDL_KEYDOWN: {
          SDL_Keycode& sym = event.key.keysym.sym;
          if (sym == SDLK_ESCAPE) {
            window->close();
          } else {
            dispatcher->Trigger(KeyDown(sym));
          }
        } break;

        case SDL_KEYUP: {
          SDL_Keycode& sym = event.key.keysym.sym;
          dispatcher->Trigger(KeyUp(sym));
        } break;
      }
    }
  }
};