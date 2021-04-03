#pragma once

#include <immintrin.h>

#include <Engine/Component/Component.hpp>

class Transform : public Component {
public:
  RTTI_DECLARATION(Transform)
  __m128* trans;  // matrix 4x4

  Transform() { trans = new __m128[4]; }

  void translate(float vx, float vy, float vz, float vw) {
    __m128 x = _mm_set1_ps(vx);
    __m128 y = _mm_set1_ps(vy);
    __m128 z = _mm_set1_ps(vz);
    __m128 w = _mm_set1_ps(vw);

    __m128 p1 = _mm_mul_ps(x, trans[0]);
    __m128 p2 = _mm_mul_ps(y, trans[1]);
    __m128 p3 = _mm_mul_ps(z, trans[2]);
    __m128 p4 = _mm_mul_ps(w, trans[3]);

    (*trans) = _mm_add_ps(_mm_add_ps(p1, p2), _mm_add_ps(p3, p4));
  }
};