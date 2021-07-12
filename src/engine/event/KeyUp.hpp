#pragma once

#include <engine/event/IEventKey.hpp>

class KeyUp final : public IEventKey {
 public:
  RTTI_DEFINITION(KeyUp, IEventKey)

  inline KeyUp(int key_code) : key_code(key_code) {}
  inline int key() const { return key_code; }

 private:
  int key_code = -1;
};