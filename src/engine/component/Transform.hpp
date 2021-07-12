#pragma once

#include <immintrin.h>

#include <cmath>
#include <engine/ecs/IComponent.hpp>
#include <iostream>

#define MakeShuffleMask(x, y, z, w) (x | (y << 2) | (z << 4) | (w << 6))

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzleMask(vec, mask) \
  _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vec), mask))
#define VecSwizzle(vec, x, y, z, w) \
  VecSwizzleMask(vec, MakeShuffleMask(x, y, z, w))
#define VecSwizzle1(vec, x) VecSwizzleMask(vec, MakeShuffleMask(x, x, x, x))

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x, y, z, w) \
  _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x, y, z, w))
// special shuffle
#define VecShuffle_0101(vec1, vec2) _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2) _mm_movehl_ps(vec2, vec1)

// 2x2 row major Matrix multiply A*B
static __m128 Mat2Mul(__m128 vec1, __m128 vec2) {
  return _mm_add_ps(
      _mm_mul_ps(vec1, VecSwizzle(vec2, 0, 3, 0, 3)),
      _mm_mul_ps(VecSwizzle(vec1, 1, 0, 3, 2), VecSwizzle(vec2, 2, 1, 2, 1)));
}
// 2x2 row major Matrix adjugate multiply (A#)*B
static __m128 Mat2AdjMul(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(
      _mm_mul_ps(VecSwizzle(vec1, 3, 3, 0, 0), vec2),
      _mm_mul_ps(VecSwizzle(vec1, 1, 1, 2, 2), VecSwizzle(vec2, 2, 3, 0, 1)));
}
// 2x2 row major Matrix multiply adjugate A*(B#)
static __m128 Mat2MulAdj(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(
      _mm_mul_ps(vec1, VecSwizzle(vec2, 3, 0, 3, 0)),
      _mm_mul_ps(VecSwizzle(vec1, 1, 0, 3, 2), VecSwizzle(vec2, 2, 1, 2, 1)));
}

struct alignas(16) float4 {
  union {
    struct {
      float x, y, z, w;
    };

    struct {
      __m128 data;
    };
  };

  float4() : x(0), y(0), z(0), w(0) {}
  float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

  float4& operator=(const float4& f) {
    x = f.x;
    y = f.y;
    z = f.z;
    w = f.w;
    return *this;
  }

  bool operator==(const float4& f) const {
    return (x == f.x && y == f.y && z == f.z && w == f.w);
  }
  float4 operator*(const float& f) const { return {x * f, y * f, z * f, 1}; }
  float4& operator*=(const float& f) {
    const __m128 ARx = _mm_set1_ps(f);
    this->data = _mm_mul_ps(ARx, this->data);
    return (*this);
  }

  float& operator[](const unsigned int i) {
    return ((i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w);
  }

  const float& operator[](const unsigned int i) const {
    return ((i == 0) ? x : (i == 1) ? y : (i == 2) ? z : w);
  }

  float operator*(const float4& vec) const {
    return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
  }

  float4 operator+(const float4& vec) const {
    return {x + vec.x, y + vec.y, z + vec.z, 1};
  }
  float4 operator-(const float4& vec) const {
    return {x - vec.x, y - vec.y, z - vec.z, 1};
  }
  float4 operator-() const { return {-x, -y, -z, 1}; }

  friend std::ostream& operator<<(std::ostream& os, const float4& f) {
    os << "(" << f.x << ", " << f.y << ", " << f.z << ", " << f.w << ")";
    return os;
  }
};

class Transform final : public IComponent {
 public:
  RTTI_DEFINITION(Transform, IComponent)
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

  inline float4 operator*(const float4& vec) const {
    const __m128 BCx = _mm_setr_ps(a.x, b.x, c.x, d.x);
    const __m128 BCy = _mm_setr_ps(a.y, b.y, c.y, d.y);
    const __m128 BCz = _mm_setr_ps(a.z, b.z, c.z, d.z);
    const __m128 BCw = _mm_setr_ps(a.w, b.w, c.w, d.w);

    const __m128 ARx = _mm_set1_ps(vec[0]);
    const __m128 ARy = _mm_set1_ps(vec[1]);
    const __m128 ARz = _mm_set1_ps(vec[2]);
    const __m128 ARw = _mm_set1_ps(vec[3]);

    const __m128 X = _mm_mul_ps(ARx, BCx);
    const __m128 Y = _mm_mul_ps(ARy, BCy);
    const __m128 Z = _mm_mul_ps(ARz, BCz);
    const __m128 W = _mm_mul_ps(ARw, BCw);

    float4 res;
    res.data = _mm_add_ps(_mm_add_ps(X, Y), _mm_add_ps(Z, W));
    return res;
  }

  /**
   * @brief Effectue une multiplication matricielle, tels que this = this * T
   */
  inline void dot(const float4& ta, const float4& tb, const float4& tc,
                  const float4& td) {
    for (unsigned int i = 0; i < 4; ++i) {
      __m128 ARx = _mm_set1_ps((*this)[i][0]);
      __m128 ARy = _mm_set1_ps((*this)[i][1]);
      __m128 ARz = _mm_set1_ps((*this)[i][2]);
      __m128 ARw = _mm_set1_ps((*this)[i][3]);

      __m128 X = _mm_mul_ps(ARx, ta.data);
      __m128 Y = _mm_mul_ps(ARy, tb.data);
      __m128 Z = _mm_mul_ps(ARz, tc.data);
      __m128 W = _mm_mul_ps(ARw, td.data);

      (*this)[i].data = _mm_add_ps(_mm_add_ps(X, Y), _mm_add_ps(Z, W));
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
    dot({1, 0, 0, 0}, {0, std::cos(deg), -std::sin(deg), 0},
        {0, std::sin(deg), std::cos(deg), 0}, {0, 0, 0, 1});
  }

  /**
   * @brief Effectue une rotation sur l'axe Y, de deg radians
   */
  void rotateY(float deg) {
    dot({std::cos(deg), 0, std::sin(deg), 0}, {0, 1, 0, 0},
        {-std::sin(deg), 0, std::cos(deg), 0}, {0, 0, 0, 1});
  }

  /**
   * @brief Effectue une rotation sur l'axe Z, de deg radians
   */
  void rotateZ(float deg) {
    dot({std::cos(deg), -std::sin(deg), 0, 0},
        {std::sin(deg), std::cos(deg), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1});
  }

  /**
   * @brief Effectue un redimensionnement de facteur f
   */
  void scale(float4 f) {
    dot({f.x, 0, 0, 0}, {0, f.y, 0, 0}, {0, 0, f.z, 0}, {0, 0, 0, f.w});
  }

  inline const float& x() const { return a.w; }
  inline const float& y() const { return b.w; }
  inline const float& z() const { return c.w; }

  inline float& y() { return b.w; }

  inline const float4 size() const {
    // maybe globaltolocal ..
    return {a.x, b.y, c.z, d.w};
  }

  float4& operator[](const unsigned int i) {
    return ((i == 0) ? a : (i == 1) ? b : (i == 2) ? c : d);
  }
  const float4& operator[](const unsigned int i) const {
    return ((i == 0) ? a : (i == 1) ? b : (i == 2) ? c : d);
  }

  /**
   * @brief Retourne la matrice inverse
   */
  Transform inverse() const {
    const __m128 BCx = _mm_setr_ps(a.x, a.y, a.z, a.w);
    const __m128 BCy = _mm_setr_ps(b.x, b.y, b.z, b.w);
    const __m128 BCz = _mm_setr_ps(c.x, c.y, c.z, c.w);
    const __m128 BCw = _mm_setr_ps(d.x, d.y, d.z, d.w);

    // use block matrix method
    // A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code)
    // means adjugate of A, |A| (or detA in code) is determinant, tr(A) is trace

    // sub matrices
    __m128 A = VecShuffle_0101(BCx, BCy);
    __m128 B = VecShuffle_2323(BCx, BCy);
    __m128 C = VecShuffle_0101(BCz, BCw);
    __m128 D = VecShuffle_2323(BCz, BCw);

    // determinant as (|A| |B| |C| |D|)
    __m128 detSub = _mm_sub_ps(_mm_mul_ps(VecShuffle(BCx, BCz, 0, 2, 0, 2),
                                          VecShuffle(BCy, BCw, 1, 3, 1, 3)),
                               _mm_mul_ps(VecShuffle(BCx, BCz, 1, 3, 1, 3),
                                          VecShuffle(BCy, BCw, 0, 2, 0, 2)));
    __m128 detA = VecSwizzle1(detSub, 0);
    __m128 detB = VecSwizzle1(detSub, 1);
    __m128 detC = VecSwizzle1(detSub, 2);
    __m128 detD = VecSwizzle1(detSub, 3);

    // let iM = 1/|M| * | X  Y |
    //                  | Z  W |

    // D#C
    __m128 D_C = Mat2AdjMul(D, C);
    // A#B
    __m128 A_B = Mat2AdjMul(A, B);
    // X# = |D|A - B(D#C)
    __m128 X_ = _mm_sub_ps(_mm_mul_ps(detD, A), Mat2Mul(B, D_C));
    // W# = |A|D - C(A#B)
    __m128 W_ = _mm_sub_ps(_mm_mul_ps(detA, D), Mat2Mul(C, A_B));

    // |M| = |A|*|D| + ... (continue later)
    __m128 detM = _mm_mul_ps(detA, detD);

    // Y# = |B|C - D(A#B)#
    __m128 Y_ = _mm_sub_ps(_mm_mul_ps(detB, C), Mat2MulAdj(D, A_B));
    // Z# = |C|B - A(D#C)#
    __m128 Z_ = _mm_sub_ps(_mm_mul_ps(detC, B), Mat2MulAdj(A, D_C));

    // |M| = |A|*|D| + |B|*|C| ... (continue later)
    detM = _mm_add_ps(detM, _mm_mul_ps(detB, detC));

    // tr((A#B)(D#C))
    __m128 tr = _mm_mul_ps(A_B, VecSwizzle(D_C, 0, 2, 1, 3));
    tr = _mm_hadd_ps(tr, tr);
    tr = _mm_hadd_ps(tr, tr);
    // |M| = |A|*|D| + |B|*|C| - tr((A#B)(D#C)
    detM = _mm_sub_ps(detM, tr);

    const __m128 adjSignMask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);
    // (1/|M|, -1/|M|, -1/|M|, 1/|M|)
    __m128 rDetM = _mm_div_ps(adjSignMask, detM);

    X_ = _mm_mul_ps(X_, rDetM);
    Y_ = _mm_mul_ps(Y_, rDetM);
    Z_ = _mm_mul_ps(Z_, rDetM);
    W_ = _mm_mul_ps(W_, rDetM);

    Transform r;

    // apply adjugate and store, here we combine adjugate shuffle and store
    // shuffle
    _mm_store_ps(&r[0][0], VecShuffle(X_, Y_, 3, 1, 3, 1));
    _mm_store_ps(&r[1][0], VecShuffle(X_, Y_, 2, 0, 2, 0));
    _mm_store_ps(&r[2][0], VecShuffle(Z_, W_, 3, 1, 3, 1));
    _mm_store_ps(&r[3][0], VecShuffle(Z_, W_, 2, 0, 2, 0));

    return r;
  }

  float4 globalToLocal(const float4& vec) const { return inverse() * vec; }
  float4 localToGlobal(const float4& vec) const { return (*this) * vec; }

  /**
   * @brief Intersection of two cube
   *
   * In local space, we check, for each edges of a cube, if it's intersect a
   * face of the other cube. For this, we compute a segment - plane intersection
   * and we check if the face contains the impact point
   */
  bool intersect(const Transform& trans) const {
    // https://www.geomalgorithms.com/a05-_intersect-1.html
    auto intersectSegmentPlane = [](const float4& v0, const float4& n,
                                    const float4& p0,
                                    const float4& p1) -> bool {
      const float4 w = v0 - p0;
      const float4 u = p1 - p0;

      const float s1 = (-n * w) / (n * u);

      const float4 ps1 = w + (u * s1);  // Point d'intersection P(s1)

      return (0 <= s1 && s1 <= 1) && (-1 < ps1.x && ps1.x < 1 && -1 < ps1.y &&
                                      ps1.y < 1 && -1 < ps1.z && ps1.z < 1);
    };

    // We are in local world, so coordinate are easy to determinate

    // center of each face
    static const float4 faces[6] = {
        {1, 0, 0, 1},  {0, 1, 0, 1},  {0, 0, 1, 1},
        {-1, 0, 0, 1}, {0, -1, 0, 1}, {0, 0, -1, 1},
    };

    // each vertex of a cube
    static const float4 vertices[8] = {
        {1, 1, 1, 1},  {1, -1, -1, 1}, {-1, 1, -1, 1}, {-1, -1, 1, 1},
        {-1, 1, 1, 1}, {1, 1, -1, 1},  {1, -1, 1, 1},  {-1, -1, -1, 1},
    };

    // each edge of a cube
    static const float4 edges[12][2] = {
        {vertices[0], vertices[4]}, {vertices[0], vertices[5]},
        {vertices[0], vertices[6]}, {vertices[1], vertices[6]},
        {vertices[1], vertices[5]}, {vertices[1], vertices[7]},
        {vertices[2], vertices[4]}, {vertices[2], vertices[5]},
        {vertices[2], vertices[6]}, {vertices[3], vertices[4]},
        {vertices[3], vertices[6]}, {vertices[3], vertices[7]},
    };

    // For each face of the cube
    for (int i = 0; i < 6; i++) {
      // We compute v0 and normal of the face's plane
      const float4 v0 = faces[i];
      const float4 n = faces[i];  // normalized normal

      for (int j = 0; j < 8; j++) {
        const float4 p0 = globalToLocal(trans.localToGlobal(edges[j][0]));
        const float4 p1 = globalToLocal(trans.localToGlobal(edges[j][1]));

        if (intersectSegmentPlane(v0, n, p0, p1)) {
          return true;
        }
      }
    }
    return false;
  }
};