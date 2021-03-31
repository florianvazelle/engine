#include <Engine/System/ThreadPoolSystem.hpp>


ThreadPoolSystem::ThreadPoolSystem() : m_function_queue(), m_lock(), m_data_condition(), m_accept_functions(true) {}

ThreadPoolSystem::~ThreadPoolSystem() {}

void ThreadPoolSystem::push(std::function<void()> func) {
  std::unique_lock<std::mutex> lock(m_lock);
  m_function_queue.push(func);
  // when we send the notification immediately, the consumer will try to get the lock , so unlock asap
  lock.unlock();
  m_data_condition.notify_one();
}

void ThreadPoolSystem::done() {
  std::unique_lock<std::mutex> lock(m_lock);
  m_accept_functions = false;
  lock.unlock();
  // when we send the notification immediately, the consumer will try to get the lock , so unlock asap
  m_data_condition.notify_all();
  // notify all waiting threads.
}

void ThreadPoolSystem::infinite_loop_func() {
  std::function<void()> func;
  while (true) {
    {
      std::unique_lock<std::mutex> lock(m_lock);
      m_data_condition.wait(lock, [this]() { return !m_function_queue.empty() || !m_accept_functions; });
      if (!m_accept_functions && m_function_queue.empty()) {
        // lock will be release automatically.
        // finish the thread loop and let it join in the main thread.
        return;
      }
      func = m_function_queue.front();
      m_function_queue.pop();
      // release the lock
    }
    func();
  }
}