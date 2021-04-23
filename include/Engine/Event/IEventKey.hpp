#pragma once

#include <Engine/Common/RTTI.hpp>
#include <Engine/Event/IEvent.hpp>

class IEventKey : public IEvent {
 public:
  RTTI_DECLARATION

  virtual inline int key() const = 0;
};