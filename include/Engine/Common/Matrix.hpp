#pragma once

#include <stdexcept>

using uint = unsigned int;

template <class T, uint m, uint n> class Matrix {
public:
  Matrix();

  T& operator()(const uint row, const uint col);

private:
  T data[m * n];
};

template <class T, uint m, uint n> Matrix<T, m, n>::Matrix() {
  if (m == 0 || n == 0) {
    throw std::invalid_argument("received zero as argument");
  }

  data = new T[m * n];  // TODO : maybe replace new by pool alloc
}

template <class T, uint m, uint n> T& Matrix<T, m, n>::operator()(const uint row, const uint col) {
  return this->data[row * n + col];
}