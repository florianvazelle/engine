#pragma once

#include <memory>

#include <Engine/Core/Engine.hpp>
#include <Engine/Core/Input.hpp>
#include <Engine/Core/Timer.hpp>

#include "spdlog/spdlog.h"

using SPC = std::shared_ptr<Clock>;
using SPI = std::shared_ptr<Input>;
using SPE = std::shared_ptr<Engine>;

class Context {
public:
  Context(SPC c, SPI i, SPE e) : clock(c), input(i), engine(e) {}
  ~Context() { spdlog::info("Context is destoy!"); }

  inline Clock* c() const { return clock.get(); };
  inline Input* i() const { return input.get(); };
  inline Engine* e() const { return engine.get(); };

private:
  SPC clock;
  SPI input;
  SPE engine;
};