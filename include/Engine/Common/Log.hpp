#pragma once

#include "spdlog/spdlog.h"

// #ifdef DEBUG
#define LOG(str)                                                            \
  spdlog::set_pattern("[%H:%M:%S] [%^%l%$] [thread %t] [" __FILE__ "] %v"); \
  spdlog::info(str);
// #else
// #  define LOG(str)
// #endif