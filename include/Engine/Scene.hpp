#pragma once

#include <vector>

#include <Engine/Common/Entity.hpp>

class Scene {
public:
  virtual void preload()                = 0;
  virtual void create()                 = 0;
  virtual void update(double deltaTime) = 0;
  virtual void destroy()                = 0;

private:
  std::vector<Entity> entities;
};