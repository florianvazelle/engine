#include <doctest.h>

#include <engine/async/ThreadPool.hpp>

TEST_CASE("ThreadPool") {
  std::atomic<int> count = 0;
  
  ThreadPool pool(1);
  std::vector<std::future<void>> results(1);
  results[0] = pool.push([&]() { count = 2; });
  results[0].get();

  CHECK(count.load() == 2);
}