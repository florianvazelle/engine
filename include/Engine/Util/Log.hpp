#pragma once

#include <SDL2/SDL_error.h>

#include <cassert>
#include <iostream>

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
#define LOG_ERROR std::cout << "[ERROR]:    "

// Log a warning.
#define LOG_WARNING std::cout << "[WARNING]:  "

// Log some information.
#define LOG_INFO std::cout << "[INFO]:     "

// Flush the log. Also ends the current line.
#define LOG_FLUSH std::endl

// Provide a NewLine in a log.
#define LOG_NEWLINE "\n"

// Convenience function.
inline void throw_sdl2_exception(std::string message) {
  message += "\n[SDL2]:   ";
  message += SDL_GetError();

  LOG(LOG_ERROR, message);
  throw std::runtime_error(message);
}