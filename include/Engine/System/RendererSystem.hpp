#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <Engine/Common/ThreadPool.hpp>
#include <Engine/System/ISystem.hpp>

class RendererSystem : public ISystem {
 public:
  RTTI_DECLARATION
  ~RendererSystem() {}

  void update(Context& context);
};