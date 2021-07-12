/**
 * @file NoMove.hpp
 * @brief Define NoMove class
 */

#pragma once

/**
 * @brief A class to prohibit move.
 */
struct NoMove {
  NoMove() = default;

  // move assignment operator
  NoMove& operator=(NoMove&& rhs) = delete;

  // move constructor
  NoMove(const NoMove&& rhs) = delete;

 protected:
  ~NoMove() = default;
};