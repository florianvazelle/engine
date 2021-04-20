#pragma once

#include <Engine/Event/IEvent.hpp>

class KeyUp final : public IEvent {
 public:
  RTTI_DECLARATION

  inline KeyUp(int key_code) : key_code(key_code) {}
  inline int key() const { return key_code; }

 private:
  int key_code = -1;
};