#pragma once

#include <engine/event/EventCallback.hpp>
#include <engine/event/IEvent.hpp>
#include <engine/meta/RTTI.hpp>
#include <engine/meta/Singleton.hpp>
#include <map>
#include <memory>

class Dispatcher : public Singleton<Dispatcher> {
  friend class Singleton<Dispatcher>;

 public:
  template <typename T, typename E>
  void RegisterAction(T* instance, void (T::*function)(E*)) {
    const RTTI& id = E::rtti;

    if (inputEvents.find(id) == inputEvents.end()) {
      inputEvents.insert({id, std::make_shared<EventCallback<T, E>>(instance, function)});
    }
  }

  template <typename T>
  void Trigger(const T& event) {
    const RTTI& id = T::rtti;

    if (inputEvents.find(id) != inputEvents.end()) {
      inputEvents[id]->Trigger(event);
    }
  }

 private:
  Dispatcher() {}
  ~Dispatcher() {}

  std::map<RTTI, std::shared_ptr<IEventCallback>> inputEvents;
};