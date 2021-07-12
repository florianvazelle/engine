#pragma once

#include <functional>
#include <future>
#include <memory>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class ThreadPool {
 private:
  std::vector<std::thread> workers;                    // Liste de nos threads (pour les join)
  std::queue<std::function<void()>> m_function_queue;  // Queue des taches

  // Synchronization
  std::mutex m_lock;
  std::condition_variable m_data_condition;
  std::atomic<bool> m_accept_functions;

 public:
  /**
   * @brief Le constructeur démarre un certain nombre de thread (workers)
   */
  explicit ThreadPool(size_t threads) : m_accept_functions(true) {
    for (size_t i = 0; i < threads; ++i)
      workers.emplace_back([this] {
        while (true) {
          std::function<void()> func;

          {
            // Le mutex sera déverrouillé, en sortant du scope, car le
            // desctuteur du lock sera appelé (RAII)
            std::unique_lock<std::mutex> lock(this->m_lock);
            this->m_data_condition.wait(lock, [this] {
              return !this->m_accept_functions || !this->m_function_queue.empty();
            });
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

  /**
   * @brief Le destructeur join tout les threads
   */
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(m_lock);
      m_accept_functions = false;
    }
    m_data_condition.notify_all();
    for (std::thread& worker : workers) worker.join();
  }

  /**
   * @brief Permet d'ajouter une nouvelle tache à la ThreadPool
   */
  template <class F, class... Args>
  auto push(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto func = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = func->get_future();
    {
      std::unique_lock<std::mutex> lock(m_lock);

      // On bloque l'ajout de nouvelle tache, après avoir stoper la ThreadPool
      if (!m_accept_functions)
        throw std::runtime_error("ThreadPool is stopped, you cannot push new task!");

      m_function_queue.emplace([func]() { (*func)(); });
    }
    m_data_condition.notify_one();
    return res;
  }
};
