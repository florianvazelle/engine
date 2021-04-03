#pragma once

#include "spdlog/spdlog.h"

// #ifdef DEBUG
#define LOG(str)                                                              \
  {                                                                           \
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] [thread %t] [" __FILE__ "] %v"); \
    spdlog::info(str);                                                        \
  }

#define LOG_WARN(str)                                                         \
  {                                                                           \
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] [thread %t] [" __FILE__ "] %v"); \
    spdlog::warn(str);                                                        \
  }
// #else
// #  define LOG(str)
// #  define LOG_WARN(str)
// #endif