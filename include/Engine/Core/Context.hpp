#pragma once

#include <Engine/Common/Log.hpp>
#include <Engine/Core/Engine.hpp>
#include <Engine/Core/Input.hpp>
#include <Engine/Core/Timer.hpp>
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

  inline float deltaTime() const {
    double elapsedTime = m_clock->elpsTime();

    // tout lag est maximise 100 ms (1/10 de seconde)
    // cela permet d'eviter de faire sauter le moteur en cas de breakpoint ou
    // lag enorme alternativement on peut appliquer une correction en
    // extrapolant a partir du temps ecoule
    if (elapsedTime > 0.10) elapsedTime = 0.10;

    return static_cast<float>(elapsedTime);
  };

 private:
  SPC m_clock;
  SPI m_input;
  SPW m_window;
  SPE m_engine;
};