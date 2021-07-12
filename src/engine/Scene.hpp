#pragma once

#include <engine/ecs/Entity.hpp>
#include <vector>

class Scene {
 public:
  virtual void preload() = 0;
  virtual void create() = 0;
};