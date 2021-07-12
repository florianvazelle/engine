#pragma once

#include <engine/meta/Log.hpp>
#include <engine/meta/Singleton.hpp>
#include <memory>

class Clock;
class Input;
class Window;
class Engine;

class Context : public Singleton<Context> {
  friend class Singleton<Context>;

 public:
  inline Clock* clock() const { return m_clock.get(); }
  inline Input* input() const { return m_input.get(); }
  inline Window* window() const { return m_window.get(); }
  inline Engine* engine() const { return m_engine.get(); }

 private:
  Context()
      : m_clock(std::make_unique<Clock>()),
        m_input(std::make_unique<Input>()),
        m_window(std::make_unique<Window>()),
        m_engine(std::make_unique<Engine>()) {}
  ~Context() { LOG(LOG_INFO, "[Context] desctruction.."); }

  std::unique_ptr<Clock> m_clock;
  std::unique_ptr<Input> m_input;
  std::unique_ptr<Window> m_window;
  std::unique_ptr<Engine> m_engine;
};