#pragma once

#include <engine/event/IEventKey.hpp>

class KeyDown final : public IEventKey {
 public:
  RTTI_DEFINITION(KeyDown, IEventKey)

  inline KeyDown(int key_code) : key_code(key_code) {}
  inline int key() const { return key_code; }

 private:
  int key_code = -1;
};