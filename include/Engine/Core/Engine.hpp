#pragma once

#include <memory>
#include <vector>

#include <Engine/Scene.hpp>
#include <Engine/System/System.hpp>

class Context;

class Engine {
public:
  void Update(Context& context);
};