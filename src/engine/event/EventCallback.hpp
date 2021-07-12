#pragma once

#include <engine/event/IEvent.hpp>

class IEventCallback {
 public:
  virtual void Trigger(const IEvent&) = 0;
};

template <typename T, typename E>
class EventCallback : public IEventCallback {
 public:
  EventCallback(T* instance, void (T::*function)(E*))
      : instance(instance), function(function) {}

  void Trigger(const IEvent& event) { (instance->*function)((E*)(&event)); }

 private:
  T* instance;
  void (T::*function)(E*);
};