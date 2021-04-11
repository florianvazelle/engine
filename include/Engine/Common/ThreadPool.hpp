#pragma once

#include <functional>
#include <future>
#include <queue>
#include <thread>
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
  ThreadPool(size_t);

  /**
   * @brief Le destructeur join tout les threads
   */
  ~ThreadPool();

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
