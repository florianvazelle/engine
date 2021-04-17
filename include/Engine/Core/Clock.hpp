#pragma once

#include <SDL2/SDL_timer.h>

#include <Engine/Util/Log.hpp>
#include <chrono>
#include <functional>
#include <vector>

class Clock {
 public:
  inline void Initialize() {
    time = 0.0;
    accumulator = 0.0;
    current_time = SDL_GetTicks();
    new_time = 0.0;
    frame_time = 0.0;
  }

  inline void Update() {
    LOG(LOG_INFO, "[Clock] Update!");

    new_time = SDL_GetTicks();
    frame_time = new_time - current_time;
    current_time = new_time;

    accumulator += frame_time;
  }

  inline void Increment(const double dt) {
    accumulator -= dt;
    time += dt;
  }

  inline float deltaTime() const { return accumulator; }

 private:
  double time, accumulator, current_time, new_time, frame_time;
};