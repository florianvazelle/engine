#pragma once

#include <chrono>
#include <functional>
#include <vector>

struct TimeSource {
  using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
  static TimePoint now() { return std::chrono::high_resolution_clock::now(); }
};

struct Timer {
  double Delay;
  double CurrentTime;
  bool Repeat;
};

class Clock {
public:
  Clock();

  void Update();
  void AddTimer(Timer& timer, std::function<void(void)> event) { m_Timers.push_back({timer, event}); }

  inline double elpsTime() const { return ElapsedTime; }

private:
  std::vector<std::pair<Timer, std::function<void()>>> m_Timers;

  TimeSource::TimePoint TimePointAtStartup;
  TimeSource::TimePoint PreviousTimePoint;
  TimeSource::TimePoint CurrentTimePoint;

  double TimeSinceStartup = 0.0;
  double ElapsedTime      = 0.0;
};