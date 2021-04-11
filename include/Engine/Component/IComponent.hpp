#pragma once

#include <Engine/Common/RTTI.hpp>

/**
 * @brief IComponent is a pure interface
 */
class IComponent {
 public:
  RTTI_DECLARATION
  // ...
  // ... no data members ...
  // ...
  virtual ~IComponent() = default;
};