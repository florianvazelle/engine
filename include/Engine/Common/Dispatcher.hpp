#pragma once

#include <Engine/Common/RTTI.hpp>
#include <Engine/Common/Singleton.hpp>
#include <Engine/Event/EventCallback.hpp>
#include <Engine/Event/IEvent.hpp>
#include <map>
#include <memory>

class Dispatcher : public Singleton<Dispatcher> {
  friend class Singleton<Dispatcher>;

 public:
  template <typename T, typename E>
  void RegisterAction(T* instance, void (T::*function)(E*)) {
    const RTTI::type& id = E::rtti.id();

    if (inputEvents.find(id) == inputEvents.end()) {
      inputEvents.insert({id, std::make_shared<EventCallback<T, E>>(instance, function)});
    }
  }

  template <typename T>
  void Trigger(const T& event) {
    const RTTI::type& id = T::rtti.id();

    if (inputEvents.find(id) != inputEvents.end()) {
      inputEvents[id]->Trigger(event);
    }
  }

 private:
  Dispatcher() {}
  ~Dispatcher() {}

  std::map<RTTI::type, std::shared_ptr<IEventCallback>> inputEvents;
};