#include <Engine/Common/Manager.hpp>

std::atomic<Manager*> Manager::s_instance{nullptr};
std::mutex Manager::s_mutex;

Manager* Manager::GetInstance() {
  Manager* p = s_instance.load(std::memory_order_acquire);
  if (p == nullptr) {  // 1st check
    std::lock_guard<std::mutex> lock(s_mutex);
    p = s_instance.load(std::memory_order_relaxed);
    if (p == nullptr) {  // 2nd (double) check
      p = new Manager();
      s_instance.store(p, std::memory_order_release);
    }
  }
  return p;
}
