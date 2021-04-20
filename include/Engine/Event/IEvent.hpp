#pragma once

#include <Engine/Common/RTTI.hpp>

class IEvent {
 public:
  RTTI_DECLARATION

  virtual inline int key() const = 0;
};