#pragma once

struct KeyDown final {
  inline KeyDown(int key_code) : m_keycode(key_code) {}
  int m_keycode = -1;
};