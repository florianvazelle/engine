#pragma once

#include <immintrin.h>

#include <Engine/Component/IComponent.hpp>
#include <cmath>

struct alignas(16) float4 {
  float x, y, z, w;

  float4() : x(0), y(0), z(0), w(0) {}
  float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  bool operator==(const float4& f) const { return (x == f.x && y == f.y && z == f.z && w == f.w); }
  float4 operator*(const float& f) const { return {x * f, y * f, z * f, w * f}; }
  float4& operator*=(const float& f) {
    this->x *= f;
    this->y *= f;
    this->z *= f;
    this->w *= f;
    return (*this);
  }

  float& operator[](const unsigned int i) {
    return ((i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w);
  }
  const float& operator[](const unsigned int i) const {
    return ((i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w);
  }
};

class Transform : public IComponent {
 public:
  RTTI_DECLARATION
  float4 a, b, c, d;

  /**
   * [[a.x, a.y, a.z, a.w],
   *  [b.x, b.y, b.z, b.w],
   *  [c.x, c.y, c.z, c.w],
   *  [d.x, d.y, d.z, d.w]]
   */

  Transform() { identity(); }

  void identity() {
    a = float4(1, 0, 0, 0);
    b = float4(0, 1, 0, 0);
    c = float4(0, 0, 1, 0);
    d = float4(0, 0, 0, 1);
  }

  /**
   * @brief Effectue une multiplication matricielle
   */
  void dot(const float4& ta, const float4& tb, const float4& tc, const float4& td) {
    const __m128 BCx = _mm_setr_ps(ta.x, ta.y, ta.z, ta.w);
    const __m128 BCy = _mm_setr_ps(tb.x, tb.y, tb.z, tb.w);
    const __m128 BCz = _mm_setr_ps(tc.x, tc.y, tc.z, tc.w);
    const __m128 BCw = _mm_setr_ps(td.x, td.y, td.z, td.w);

    for (unsigned int i = 0; i < 4; ++i) {
      __m128 ARx = _mm_set1_ps((*this)[i][0]);
      __m128 ARy = _mm_set1_ps((*this)[i][1]);
      __m128 ARz = _mm_set1_ps((*this)[i][2]);
      __m128 ARw = _mm_set1_ps((*this)[i][3]);

      __m128 X = _mm_mul_ps(ARx, BCx);
      __m128 Y = _mm_mul_ps(ARy, BCy);
      __m128 Z = _mm_mul_ps(ARz, BCz);
      __m128 W = _mm_mul_ps(ARw, BCw);

      __m128 R = _mm_add_ps(_mm_add_ps(X, Y), _mm_add_ps(Z, W));
      _mm_store_ps(&(*this)[i][0], R);
    }
  }

  /**
   * @brief Effectue une translation de vecteur (x, y, z, w)
   */
  void translate(const float4& vec) {
    dot({1, 0, 0, vec.x}, {0, 1, 0, vec.y}, {0, 0, 1, vec.z}, {0, 0, 0, vec.w});
  }

  /**
   * @brief Effectue une rotation sur l'axe X, de deg radians
   */
  void rotateX(float deg) {
    dot({1, 0, 0, 0}, {0, std::cos(deg), -std::sin(deg), 0}, {0, std::sin(deg), std::cos(deg), 0},
        {0, 0, 0, 1});
  }

  /**
   * @brief Effectue une rotation sur l'axe Y, de deg radians
   */
  void rotateY(float deg) {
    dot({std::cos(deg), 0, std::sin(deg), 0}, {0, 1, 0, 0}, {-std::sin(deg), 0, std::cos(deg), 0},
        {0, 0, 0, 1});
  }

  /**
   * @brief Effectue une rotation sur l'axe Z, de deg radians
   */
  void rotateZ(float deg) {
    dot({std::cos(deg), -std::sin(deg), 0, 0}, {std::sin(deg), std::cos(deg), 0, 0}, {0, 0, 1, 0},
        {0, 0, 0, 1});
  }

  /**
   * @brief Effectue un redimensionnement de facteur f
   */
  void scale(float f) { dot({f, 0, 0, 0}, {0, f, 0, 0}, {0, 0, f, 0}, {0, 0, 0, 1}); }

  inline const float& x() const { return a.w; }
  inline const float& y() const { return b.w; }
  inline const float& z() const { return c.w; }

  float4& operator[](const unsigned int i) {
    return ((i == 0) ? a : (i == 1) ? b : (i == 2) ? c : d);
  }
  const float4& operator[](const unsigned int i) const {
    return ((i == 0) ? a : (i == 1) ? b : (i == 2) ? c : d);
  }
};