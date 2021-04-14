#pragma once

#include <Engine/Common/RTTI.hpp>
#include <Engine/Core/Context.hpp>
#include <thread>
#include <vector>

/**
 * @brief ISystem is a pure interface
 */
class ISystem {
 public:
  RTTI_DECLARATION
  virtual void update(const Context& context) const = 0;
  // ...
  // ... no data members ...
  // ...
  virtual ~ISystem() = default;
};