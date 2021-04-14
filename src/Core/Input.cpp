#include <SDL2/SDL.h>

#include <Engine/Core/Context.hpp>
#include <Engine/Core/Input.hpp>

void Input::Update(const Context& context) const {
  Window* window = context.window();
  SDL_Event& event = window->m_event;

  // Process all user and system events.
  while (SDL_PollEvent(&event) != 0) {
    // https://wiki.libsdl.org/SDL_Event
    switch (event.type) {
      case SDL_QUIT:
        context.window()->close();
        break;

      case SDL_KEYDOWN:
        SDL_Keycode& sym = event.key.keysym.sym;
        if (sym == SDLK_ESCAPE) {
          context.window()->close();
        } 
        break;

      // case SDL_KEYUP:
      //   break;
    }
  }
}