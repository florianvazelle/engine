#pragma once

#include <Engine/Common/Log.hpp>
#include <Engine/Core/Clock.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/Core/Input.hpp>
#include <Engine/Core/Window.hpp>
#include <atomic>
#include <memory>
#include <mutex>

class Context {
 public:
  static Context* GetInstance();

  inline Clock* clock() const { return m_clock.get(); };
  inline Input* input() const { return m_input.get(); };
  inline Window* window() const { return m_window.get(); };
  inline Engine* engine() const { return m_engine.get(); };

  ~Context() { LOG(LOG_INFO, "[Context] desctruction.."); };

 private:
  Context()
      : m_clock(std::make_unique<Clock>()),
        m_input(std::make_unique<Input>()),
        m_window(std::make_unique<Window>()),
        m_engine(std::make_unique<Engine>()) {}

  static std::atomic<Context*> s_instance;
  static std::mutex s_mutex;

  std::unique_ptr<Clock> m_clock;
  std::unique_ptr<Input> m_input;
  std::unique_ptr<Window> m_window;
  std::unique_ptr<Engine> m_engine;
};