#pragma once

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/ThreadPool.hpp>
#include <Engine/System/ISystem.hpp>
#include <vector>

/**
 * @brief Example of a custom ISystem
 */
class BallSystem final : public ISystem {
 public:
  RTTI_DECLARATION
  ~BallSystem() {}

  void update() const;
};