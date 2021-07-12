#pragma once

#include <engine/event/IEvent.hpp>
#include <engine/meta/RTTI.hpp>

class IEventKey : public IEvent {
 public:
  RTTI_DEFINITION(IEventKey, IEvent)

  virtual inline int key() const = 0;
};