#include <Engine/Core/Input.hpp>

void Input::Update() { QuitButtonPressed = GetQuitButtonState(); }

bool Input::GetQuitButtonState() {
  //   if (_kbhit()) {
  //     int ch = _getch();
  //     if (ch == 27)  // ESC
  //       return true;
  //   }
  return false;
}