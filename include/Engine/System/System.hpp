#pragma once

#include <thread>
#include <vector>

#include <Engine/System/ThreadPoolSystem.hpp>

class System {
public:
  int num_threads;
  ThreadPoolSystem func_pool;
  std::vector<std::thread> thread_pool;

  System() : num_threads(std::thread::hardware_concurrency()), thread_pool(num_threads), func_pool() {
    for (int i = 0; i < num_threads; i++) {
      thread_pool[i] = std::thread(&ThreadPoolSystem::infinite_loop_func, &func_pool);
    }
  }

  virtual void update(double deltaTime) = 0;
};