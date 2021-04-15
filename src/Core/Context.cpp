#include <Engine/Core/Context.hpp>

std::atomic<Context*> Context::s_instance{nullptr};
std::mutex Context::s_mutex;

Context* Context::GetInstance() {
  Context* p = s_instance.load(std::memory_order_acquire);
  if (p == nullptr) {  // 1st check
    std::lock_guard<std::mutex> lock(s_mutex);
    p = s_instance.load(std::memory_order_relaxed);
    if (p == nullptr) {  // 2nd (double) check
      p = new Context();
      s_instance.store(p, std::memory_order_release);
    }
  }
  return p;
}
