#pragma once

#include <vector>

#include <Engine/Common/Entity.hpp>

class IScene {
public:
  virtual void preload()                = 0;
  virtual void create()                 = 0;
  virtual void update(double deltaTime) = 0;
};