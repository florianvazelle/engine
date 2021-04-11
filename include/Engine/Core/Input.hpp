#pragma once

class Input {
 public:
  void Update();
  bool GetQuitButtonState();

  inline bool QuitButtonIsPressed() const { return QuitButtonPressed; }

 private:
  bool QuitButtonPressed = false;
};