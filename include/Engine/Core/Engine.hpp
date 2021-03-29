#pragma once

#include <memory>
#include <vector>

#include <Engine/System/System.hpp>

class Context;

class Engine {
public:
  Engine();

  void Update(Context& context);

private:
  std::vector<std::shared_ptr<System>> systems;
};