#include <SDL2/SDL.h>

#include <Engine/Common/Log.hpp>
#include <Engine/Core/Clock.hpp>

void Clock::Initialize() {
  time = 0.0;
  accumulator = 0.0;
  current_time = SDL_GetTicks();
  new_time = 0.0;
  frame_time = 0.0;
}

void Clock::Update() {
  LOG(LOG_INFO, "[Clock] Update!");

  new_time = SDL_GetTicks();
  frame_time = new_time - current_time;
  current_time = new_time;

  accumulator += frame_time;
}

void Clock::FixedUpdate(const std::function<void(void)>& update) {
  // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl operates on milliseconds
  // not nanoseconds.
  const constexpr float dt = 1000.0f / 60.0f;

  while (accumulator >= dt) {
    update();

    accumulator -= dt;
    time += dt;
  }
}
