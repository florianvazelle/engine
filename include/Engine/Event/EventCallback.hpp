#pragma once

#include <Engine/Event/IEvent.hpp>

class IEventCallback {
 public:
  virtual void Trigger(const IEvent&) = 0;
};

template <typename T>
class EventCallback : public IEventCallback {
 public:
  EventCallback(T* instance, void (T::*function)(const IEvent&))
      : instance(instance), function(function) {}

  void Trigger(const IEvent& event) { (instance->*function)(event); }

 private:
  T* instance;
  void (T::*function)(const IEvent&);
};