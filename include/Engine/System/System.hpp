#pragma once

#include <thread>
#include <vector>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Common/ThreadPool.hpp>

class System {
public:
  RTTI_DECLARATION(System)
  size_t num_threads;

  System() : num_threads(std::thread::hardware_concurrency()) {}

  virtual void update(double deltaTime) = 0;
};