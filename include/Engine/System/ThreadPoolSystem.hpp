#pragma once

#include <Engine/System/System.hpp>
#include <vector>
#include <thread>
#include <future>
#include <queue>

class ThreadPoolSystem {

  private:
  std::queue<std::function<void()>> m_function_queue;
  std::mutex m_lock;
  std::condition_variable m_data_condition;
  std::atomic<bool> m_accept_functions;

public:

  ThreadPoolSystem();
  ~ThreadPoolSystem();
  void push(std::function<void()> func);
  void done();
  void infinite_loop_func();
};
