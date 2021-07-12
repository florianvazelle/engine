#pragma once

#include <SDL2/SDL_error.h>

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

enum Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 32,
  FG_BLUE = 34,
  FG_DEFAULT = 39,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_BLUE = 44,
  BG_DEFAULT = 49
};

class Modifier {
  Code code;

 public:
  explicit Modifier(Code pCode) : code(pCode) {}
  friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
    return os << "\033[" << mod.code << "m";
  }
};

/**
 * Example usage:
 * LOG_ERROR << "Woops." << LOG_NEWLINE;
 * OR
 * LOG_ERROR << "Woops." << LOG_FLUSH;
 * OR
 * LOG(LOG_ERROR, "Woops.");
 */

// Log something to console.
#define LOG(level, msg) level << msg << "\n"

// Log an error message.
#define LOG_ERROR std::cout << Modifier(FG_RED) << "[ERROR]:    "

// Log a warning.
#define LOG_WARNING std::cout << Modifier(FG_YELLOW) << "[WARNING]:  "

// Log some information.
#define LOG_INFO std::cout << Modifier(FG_BLUE) << "[INFO]:     "

// Flush the log. Also ends the current line.
#define LOG_FLUSH std::endl

// Provide a NewLine in a log.
#define LOG_NEWLINE "\n"

// Convenience function.
inline void throw_sdl2_exception(std::string message) {
  message += "\n[SDL2]:   ";
  message += SDL_GetError();

  throw std::runtime_error(message);
}