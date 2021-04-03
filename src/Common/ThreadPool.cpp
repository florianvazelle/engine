#include <Engine/Common/ThreadPool.hpp>

ThreadPool::ThreadPool(size_t threads) : m_accept_functions(true) {
  for (size_t i = 0; i < threads; ++i)
    workers.emplace_back([this] {
      while (true) {
        std::function<void()> func;

        {
          // Le mutex sera déverrouillé, en sortant du scope, car le desctuteur du lock sera appelé (RAII)
          std::unique_lock<std::mutex> lock(this->m_lock);
          this->m_data_condition.wait(lock,
                                      [this] { return !this->m_accept_functions || !this->m_function_queue.empty(); });
          if (!this->m_accept_functions && this->m_function_queue.empty()) {
            // lock will be release automatically.
            // finish the thread loop and let it join in the main thread.
            return;
          }
          func = std::move(this->m_function_queue.front());
          this->m_function_queue.pop();
        }

        func();
      }
    });
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(m_lock);
    m_accept_functions = false;
  }
  m_data_condition.notify_all();
  for (std::thread& worker : workers) worker.join();
}