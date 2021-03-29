#pragma once

#include <vector>

#include <Engine/Entity.hpp>

class Scene {
public:
  virtual void preload()                = 0;
  virtual void create()                 = 0;
  virtual void update(double deltaTime) = 0;

private:
  std::vector<Entity> entities;
};