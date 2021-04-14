#pragma once

#include <chrono>
#include <functional>
#include <vector>

class Clock {
 public:
  void Initialize();
  void Update();
  void FixedUpdate(const std::function<void(void)>& update);

  inline float deltaTime() const { return accumulator; }

 private:
  float time, accumulator, current_time, new_time, frame_time;
};