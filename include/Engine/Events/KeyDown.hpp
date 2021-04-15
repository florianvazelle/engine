#pragma once

struct KeyUp final {
  inline KeyUp(int key_code) : m_keycode(key_code) {}
  int m_keycode = -1;
};