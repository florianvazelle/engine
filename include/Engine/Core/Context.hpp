#pragma once

#include <Engine/Common/Log.hpp>
#include <Engine/Core/Clock.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/Core/Input.hpp>
#include <Engine/Core/Window.hpp>
#include <memory>

using SPC = std::shared_ptr<Clock>;
using SPI = std::shared_ptr<Input>;
using SPW = std::shared_ptr<Window>;
using SPE = std::shared_ptr<Engine>;

class Context {
 public:
  Context()
      : m_clock(std::make_shared<Clock>()),
        m_input(std::make_shared<Input>()),
        m_window(std::make_shared<Window>()),
        m_engine(std::make_shared<Engine>()) {}
  ~Context() { LOG(LOG_INFO, "Context is destroy!"); }

  inline Clock* clock() const { return m_clock.get(); };
  inline Input* input() const { return m_input.get(); };
  inline Window* window() const { return m_window.get(); };
  inline Engine* engine() const { return m_engine.get(); };

 private:
  SPC m_clock;
  SPI m_input;
  SPW m_window;
  SPE m_engine;
};