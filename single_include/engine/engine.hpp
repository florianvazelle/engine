#pragma once

// #include <engine/Game.hpp>

// #include <engine/Game.hpp>

// #include <engine/Scene.hpp>

// #include <engine/ecs/Entity.hpp>

#include <cstdint>

#ifndef MAX_ENTITIES
  #define MAX_ENTITIES 10
#endif

using Entity = uint32_t;
#include <vector>

class Scene {
 public:
  virtual void preload() = 0;
  virtual void create() = 0;
};
// #include <engine/component/Transform.hpp>

#include <immintrin.h>

#include <cmath>
// #include <engine/ecs/IComponent.hpp>

// #include <engine/meta/RTTI.hpp>

// #include <engine/meta/Hash.hpp>

#include <cstdint>
#include <string_view>  // C++17

/**
 * Use this to hash string at compile-time
 */

static constexpr uint32_t crc_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L,
    0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL,
    0xe7b82d07L, 0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL,
    0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
    0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL, 0x35b5a8faL, 0x42b2986cL,
    0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL,
    0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
    0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL,
    0xb6662d3dL, 0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL,
    0x086d3d2dL, 0x91646c97L, 0xe6635c01L, 0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
    0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL,
    0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L, 0x4db26158L, 0x3ab551ceL,
    0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
    0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L,
    0xce61e49fL, 0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L,
    0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L,
    0x9dd277afL, 0x04db2615L, 0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L, 0x8708a3d2L, 0x1e01f268L,
    0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L,
    0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L, 0xd6d6a3e8L,
    0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
    0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L,
    0x220216b9L, 0x5505262fL, 0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L,
    0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
    0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L, 0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL,
    0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L, 0x88085ae6L,
    0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
    0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL,
    0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L,
    0x47b2cf7fL, 0x30b5ffe9L, 0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
    0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL};

constexpr uint32_t crc32(const std::string_view& str) {
  uint32_t crc = 0xffffffff;
  for (auto c : str) crc = (crc >> 8) ^ crc_table[(crc ^ c) & 0xff];
  return crc ^ 0xffffffff;
}

using RTTI = uint32_t;

#define RTTI_DEFINITION_BASE(ClassName)                                  \
 public:                                                                 \
  static constexpr RTTI rtti = crc32(#ClassName);                        \
  static constexpr bool IsExactly(const RTTI& id) { return id == rtti; } \
  static constexpr bool IsA(const RTTI& id) { return IsExactly(id); }

#define RTTI_DEFINITION(ClassName, ParentClass)                          \
 private:                                                                \
  using SuperClass = ParentClass;                                        \
                                                                         \
 public:                                                                 \
  static constexpr RTTI rtti = crc32(#ClassName);                        \
  static constexpr bool IsExactly(const RTTI& id) { return id == rtti; } \
  static constexpr bool IsA(const RTTI& id) { return IsExactly(id) || SuperClass::IsA(id); }

/**
 * @brief IComponent is a pure interface
 */
class IComponent {
 public:
  RTTI_DEFINITION_BASE(IComponent)
  virtual ~IComponent() = default;
};
#include <iostream>

#define MakeShuffleMask(x, y, z, w) (x | (y << 2) | (z << 4) | (w << 6))

// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
#define VecSwizzleMask(vec, mask) _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(vec), mask))
#define VecSwizzle(vec, x, y, z, w) VecSwizzleMask(vec, MakeShuffleMask(x, y, z, w))
#define VecSwizzle1(vec, x) VecSwizzleMask(vec, MakeShuffleMask(x, x, x, x))

// return (vec1[x], vec1[y], vec2[z], vec2[w])
#define VecShuffle(vec1, vec2, x, y, z, w) _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x, y, z, w))
// special shuffle
#define VecShuffle_0101(vec1, vec2) _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2) _mm_movehl_ps(vec2, vec1)

// 2x2 row major Matrix multiply A*B
static __m128 Mat2Mul(__m128 vec1, __m128 vec2) {
  return _mm_add_ps(_mm_mul_ps(vec1, VecSwizzle(vec2, 0, 3, 0, 3)),
                    _mm_mul_ps(VecSwizzle(vec1, 1, 0, 3, 2), VecSwizzle(vec2, 2, 1, 2, 1)));
}
// 2x2 row major Matrix adjugate multiply (A#)*B
static __m128 Mat2AdjMul(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(_mm_mul_ps(VecSwizzle(vec1, 3, 3, 0, 0), vec2),
                    _mm_mul_ps(VecSwizzle(vec1, 1, 1, 2, 2), VecSwizzle(vec2, 2, 3, 0, 1)));
}
// 2x2 row major Matrix multiply adjugate A*(B#)
static __m128 Mat2MulAdj(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(_mm_mul_ps(vec1, VecSwizzle(vec2, 3, 0, 3, 0)),
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

  bool operator==(const float4& f) const { return (x == f.x && y == f.y && z == f.z && w == f.w); }
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

  float4 operator+(const float4& vec) const { return {x + vec.x, y + vec.y, z + vec.z, 1}; }
  float4 operator-(const float4& vec) const { return {x - vec.x, y - vec.y, z - vec.z, 1}; }
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
  inline void dot(const float4& ta, const float4& tb, const float4& tc, const float4& td) {
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
  void scale(float4 f) { dot({f.x, 0, 0, 0}, {0, f.y, 0, 0}, {0, 0, f.z, 0}, {0, 0, 0, f.w}); }

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
    __m128 detSub =
        _mm_sub_ps(_mm_mul_ps(VecShuffle(BCx, BCz, 0, 2, 0, 2), VecShuffle(BCy, BCw, 1, 3, 1, 3)),
                   _mm_mul_ps(VecShuffle(BCx, BCz, 1, 3, 1, 3), VecShuffle(BCy, BCw, 0, 2, 0, 2)));
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
    auto intersectSegmentPlane = [](const float4& v0, const float4& n, const float4& p0,
                                    const float4& p1) -> bool {
      const float4 w = v0 - p0;
      const float4 u = p1 - p0;

      const float s1 = (-n * w) / (n * u);

      const float4 ps1 = w + (u * s1);  // Point d'intersection P(s1)

      return (0 <= s1 && s1 <= 1) &&
             (-1 < ps1.x && ps1.x < 1 && -1 < ps1.y && ps1.y < 1 && -1 < ps1.z && ps1.z < 1);
    };

    // We are in local world, so coordinate are easy to determinate

    // center of each face
    static const float4 faces[6] = {
        {1, 0, 0, 1}, {0, 1, 0, 1}, {0, 0, 1, 1}, {-1, 0, 0, 1}, {0, -1, 0, 1}, {0, 0, -1, 1},
    };

    // each vertex of a cube
    static const float4 vertices[8] = {
        {1, 1, 1, 1},  {1, -1, -1, 1}, {-1, 1, -1, 1}, {-1, -1, 1, 1},
        {-1, 1, 1, 1}, {1, 1, -1, 1},  {1, -1, 1, 1},  {-1, -1, -1, 1},
    };

    // each edge of a cube
    static const float4 edges[12][2] = {
        {vertices[0], vertices[4]}, {vertices[0], vertices[5]}, {vertices[0], vertices[6]},
        {vertices[1], vertices[6]}, {vertices[1], vertices[5]}, {vertices[1], vertices[7]},
        {vertices[2], vertices[4]}, {vertices[2], vertices[5]}, {vertices[2], vertices[6]},
        {vertices[3], vertices[4]}, {vertices[3], vertices[6]}, {vertices[3], vertices[7]},
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
// #include <engine/component/Velocity.hpp>

// #include <engine/component/Transform.hpp>

// #include <engine/ecs/IComponent.hpp>

/**
 * @brief Add Velocity to an Entity, add Physical to this Entity
 */
class Velocity final : public IComponent {
 public:
  RTTI_DEFINITION(Velocity, IComponent)
  float4 direction;

  Velocity() : direction(0, 0, 0, 1) {}
};
// #include <engine/component/collider/RectCollider.hpp>

// #include <engine/ecs/IComponent.hpp>

class RectCollider final : public IComponent {
  RTTI_DEFINITION(RectCollider, IComponent)
};
// #include <engine/component/renderer/CircleRenderer.hpp>

// #include <engine/ecs/IComponent.hpp>

// #include <engine/core/Context.hpp>

// #include <engine/meta/Log.hpp>

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
// #include <engine/meta/Singleton.hpp>

#include <atomic>
#include <mutex>

/**
 * @brief Thread-safe Singleton
 *
 * https://stackoverflow.com/questions/34519073/inherit-singleton
 */
template <typename T>
class Singleton {
 public:
  /**
   * @brief Retourne une unique instance de T (double-check locking)
   */
  static T* GetInstance() noexcept(std::is_nothrow_constructible<T>::value);

 protected:
  Singleton() noexcept = default;
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  virtual ~Singleton() = default;  // to silence base class Singleton<T> has a
                                   // non-virtual destructor [-Weffc++]

  static std::atomic<T*> s_instance;
  static std::mutex s_mutex;
};

template <typename T>
std::atomic<T*> Singleton<T>::s_instance{nullptr};

template <typename T>
std::mutex Singleton<T>::s_mutex;

template <typename T>
T* Singleton<T>::GetInstance() noexcept(std::is_nothrow_constructible<T>::value) {
  T* p = s_instance.load(std::memory_order_acquire);
  if (p == nullptr) {  // 1st check
    std::lock_guard<std::mutex> lock(s_mutex);
    p = s_instance.load(std::memory_order_relaxed);
    if (p == nullptr) {  // 2nd (double) check
      p = new T();
      s_instance.store(p, std::memory_order_release);
    }
  }
  return p;
}
#include <memory>

class Clock;
class Input;
class Window;
class Engine;

class Context : public Singleton<Context> {
  friend class Singleton<Context>;

 public:
  inline Clock* clock() const { return m_clock.get(); }
  inline Input* input() const { return m_input.get(); }
  inline Window* window() const { return m_window.get(); }
  inline Engine* engine() const { return m_engine.get(); }

 private:
  Context()
      : m_clock(std::make_unique<Clock>()),
        m_input(std::make_unique<Input>()),
        m_window(std::make_unique<Window>()),
        m_engine(std::make_unique<Engine>()) {}
  ~Context() { LOG(LOG_INFO, "[Context] desctruction.."); }

  std::unique_ptr<Clock> m_clock;
  std::unique_ptr<Input> m_input;
  std::unique_ptr<Window> m_window;
  std::unique_ptr<Engine> m_engine;
};
// #include <engine/core/Window.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// #include <engine/meta/Log.hpp>

#include <string>

class Window {
 public:
  Window() : m_is_open{true}, m_window{nullptr}, m_renderer{nullptr} {}

  ~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
  }

  void create(std::string title, const int w, const int h, std::uint32_t flags) {
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
                                flags);
    if (!m_window) {
      throw_sdl2_exception("Window failed to be created.");
    }

    m_renderer =
        SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
      throw_sdl2_exception("Renderer failed to be created.");
    }
  }

  void close() noexcept { m_is_open = false; }

  bool is_open() const noexcept { return m_is_open; }
  SDL_Renderer* renderer() const noexcept { return m_renderer; }

  SDL_Event m_event;

 private:
  bool m_is_open;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};

class CircleRenderer final : public IComponent {
  RTTI_DEFINITION(CircleRenderer, IComponent)
};
// #include <engine/component/renderer/RectRenderer.hpp>

// #include <engine/core/Context.hpp>

// #include <engine/core/Window.hpp>

// #include <engine/ecs/IComponent.hpp>

class RectRenderer final : public IComponent {
  RTTI_DEFINITION(RectRenderer, IComponent)
};
// #include <engine/core/Clock.hpp>

#include <SDL2/SDL_timer.h>

#include <chrono>
// #include <engine/meta/Log.hpp>

#include <functional>
#include <vector>

class Clock {
 public:
  inline void Initialize() {
    time = 0.0;
    accumulator = 0.0;
    current_time = SDL_GetTicks();
    new_time = 0.0;
    frame_time = 0.0;
  }

  inline void Update() {
    LOG(LOG_INFO, "[Clock] Update!");

    new_time = SDL_GetTicks();
    frame_time = new_time - current_time;
    current_time = new_time;

    accumulator += frame_time;
  }

  inline void Increment(const double dt) {
    accumulator -= dt;
    time += dt;
  }

  inline float deltaTime() const { return accumulator; }

 private:
  double time, accumulator, current_time, new_time, frame_time;
};
// #include <engine/core/Engine.hpp>

// #include <engine/core/Context.hpp>

// #include <engine/factory/ComponentFactory.hpp>

// #include <engine/ecs/Entity.hpp>

// #include <engine/ecs/IComponent.hpp>

// #include <engine/meta/Macro.hpp>
/*
 * Copyright (C) 2012 William Swanson
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the names of the authors or
 * their institutions shall not be used in advertising or otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from the authors.
 */

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL5(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#ifdef _MSC_VER
  // MSVC needs more evaluations
  #define EVAL6(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
  #define EVAL(...) EVAL6(EVAL6(__VA_ARGS__))
#else
  #define EVAL(...) EVAL5(__VA_ARGS__)
#endif

#define MAP_END(...)
#define MAP_OUT

#define EMPTY()
#define DEFER(id) id EMPTY()

#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) DEFER(MAP_NEXT0)(test, next, 0)
#define MAP_NEXT(test, next) MAP_NEXT1(MAP_GET_END test, next)
#define MAP_INC(X) MAP_INC_##X

#define MAP0(f, x, peek, ...) f(x) DEFER(MAP_NEXT(peek, MAP1))(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) DEFER(MAP_NEXT(peek, MAP0))(f, peek, __VA_ARGS__)

#define MAP0_UD(f, userdata, x, peek, ...) \
  f(x, userdata) DEFER(MAP_NEXT(peek, MAP1_UD))(f, userdata, peek, __VA_ARGS__)
#define MAP1_UD(f, userdata, x, peek, ...) \
  f(x, userdata) DEFER(MAP_NEXT(peek, MAP0_UD))(f, userdata, peek, __VA_ARGS__)

#define MAP0_UD_I(f, userdata, index, x, peek, ...) \
  f(x, userdata, index)                             \
      DEFER(MAP_NEXT(peek, MAP1_UD_I))(f, userdata, MAP_INC(index), peek, __VA_ARGS__)
#define MAP1_UD_I(f, userdata, index, x, peek, ...) \
  f(x, userdata, index)                             \
      DEFER(MAP_NEXT(peek, MAP0_UD_I))(f, userdata, MAP_INC(index), peek, __VA_ARGS__)

#define MAP_LIST0(f, x, peek, ...) , f(x) DEFER(MAP_NEXT(peek, MAP_LIST1))(f, peek, __VA_ARGS__)
#define MAP_LIST1(f, x, peek, ...) , f(x) DEFER(MAP_NEXT(peek, MAP_LIST0))(f, peek, __VA_ARGS__)
#define MAP_LIST2(f, x, peek, ...) f(x) DEFER(MAP_NEXT(peek, MAP_LIST1))(f, peek, __VA_ARGS__)

#define MAP_LIST0_UD(f, userdata, x, peek, ...) \
  , f(x, userdata) DEFER(MAP_NEXT(peek, MAP_LIST1_UD))(f, userdata, peek, __VA_ARGS__)
#define MAP_LIST1_UD(f, userdata, x, peek, ...) \
  , f(x, userdata) DEFER(MAP_NEXT(peek, MAP_LIST0_UD))(f, userdata, peek, __VA_ARGS__)
#define MAP_LIST2_UD(f, userdata, x, peek, ...) \
  f(x, userdata) DEFER(MAP_NEXT(peek, MAP_LIST1_UD))(f, userdata, peek, __VA_ARGS__)

#define MAP_LIST0_UD_I(f, userdata, index, x, peek, ...) \
  , f(x, userdata, index)                                \
        DEFER(MAP_NEXT(peek, MAP_LIST1_UD_I))(f, userdata, MAP_INC(index), peek, __VA_ARGS__)
#define MAP_LIST1_UD_I(f, userdata, index, x, peek, ...) \
  , f(x, userdata, index)                                \
        DEFER(MAP_NEXT(peek, MAP_LIST0_UD_I))(f, userdata, MAP_INC(index), peek, __VA_ARGS__)
#define MAP_LIST2_UD_I(f, userdata, index, x, peek, ...) \
  f(x, userdata, index)                                  \
      DEFER(MAP_NEXT(peek, MAP_LIST0_UD_I))(f, userdata, MAP_INC(index), peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MAP_LIST(f, ...) EVAL(MAP_LIST2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and passes
 * userdata as the second parameter to each invocation, e.g. MAP_UD(f, x, a, b,
 * c) evaluates to f(a, x) f(b, x) f(c, x)
 */
#define MAP_UD(f, userdata, ...) EVAL(MAP1_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, inserts
 * commas between the results, and passes userdata as the second parameter to
 * each invocation, e.g. MAP_LIST_UD(f, x, a, b, c) evaluates to f(a, x), f(b,
 * x), f(c, x)
 */
#define MAP_LIST_UD(f, userdata, ...) \
  EVAL(MAP_LIST2_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, passes
 * userdata as the second parameter to each invocation, and the index of the
 * invocation as the third parameter, e.g. MAP_UD_I(f, x, a, b, c) evaluates to
 * f(a, x, 0) f(b, x, 1) f(c, x, 2)
 */
#define MAP_UD_I(f, userdata, ...) \
  EVAL(MAP1_UD_I(f, userdata, 0, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters, inserts
 * commas between the results, passes userdata as the second parameter to each
 * invocation, and the index of the invocation as the third parameter, e.g.
 * MAP_LIST_UD_I(f, x, a, b, c) evaluates to f(a, x, 0), f(b, x, 1), f(c, x, 2)
 */
#define MAP_LIST_UD_I(f, userdata, ...) \
  EVAL(MAP_LIST2_UD_I(f, userdata, 0, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/*
 * Because the preprocessor can't do arithmetic that produces integer literals
 * for the *_I macros, we have to do it manually. Since the number of parameters
 * is limited anyways, this is sufficient for all cases. If extra EVAL layers
 * are added, these definitions have to be extended. This is equivalent to the
 * way Boost.preprocessor does it:
 * https://github.com/boostorg/preprocessor/blob/develop/include/boost/preprocessor/arithmetic/inc.hpp
 * The *_I macros could alternatively pass C expressions such as (0), (0+1),
 * (0+1+1...) to the user macro, but passing 0, 1, 2 ... allows the user to
 * incorporate the index into C identifiers, e.g. to define a function like
 * test_##index
 * () for each macro invocation.
 */
#define MAP_INC_0 1
#define MAP_INC_1 2
#define MAP_INC_2 3
#define MAP_INC_3 4
#define MAP_INC_4 5
#define MAP_INC_5 6
#define MAP_INC_6 7
#define MAP_INC_7 8
#define MAP_INC_8 9
#define MAP_INC_9 10
#define MAP_INC_10 11
#define MAP_INC_11 12
#define MAP_INC_12 13
#define MAP_INC_13 14
#define MAP_INC_14 15
#define MAP_INC_15 16
#define MAP_INC_16 17
#define MAP_INC_17 18
#define MAP_INC_18 19
#define MAP_INC_19 20
#define MAP_INC_20 21
#define MAP_INC_21 22
#define MAP_INC_22 23
#define MAP_INC_23 24
#define MAP_INC_24 25
#define MAP_INC_25 26
#define MAP_INC_26 27
#define MAP_INC_27 28
#define MAP_INC_28 29
#define MAP_INC_29 30
#define MAP_INC_30 31
#define MAP_INC_31 32
#define MAP_INC_32 33
#define MAP_INC_33 34
#define MAP_INC_34 35
#define MAP_INC_35 36
#define MAP_INC_36 37
#define MAP_INC_37 38
#define MAP_INC_38 39
#define MAP_INC_39 40
#define MAP_INC_40 41
#define MAP_INC_41 42
#define MAP_INC_42 43
#define MAP_INC_43 44
#define MAP_INC_44 45
#define MAP_INC_45 46
#define MAP_INC_46 47
#define MAP_INC_47 48
#define MAP_INC_48 49
#define MAP_INC_49 50
#define MAP_INC_50 51
#define MAP_INC_51 52
#define MAP_INC_52 53
#define MAP_INC_53 54
#define MAP_INC_54 55
#define MAP_INC_55 56
#define MAP_INC_56 57
#define MAP_INC_57 58
#define MAP_INC_58 59
#define MAP_INC_59 60
#define MAP_INC_60 61
#define MAP_INC_61 62
#define MAP_INC_62 63
#define MAP_INC_63 64
#define MAP_INC_64 65
#define MAP_INC_65 66
#define MAP_INC_66 67
#define MAP_INC_67 68
#define MAP_INC_68 69
#define MAP_INC_69 70
#define MAP_INC_70 71
#define MAP_INC_71 72
#define MAP_INC_72 73
#define MAP_INC_73 74
#define MAP_INC_74 75
#define MAP_INC_75 76
#define MAP_INC_76 77
#define MAP_INC_77 78
#define MAP_INC_78 79
#define MAP_INC_79 80
#define MAP_INC_80 81
#define MAP_INC_81 82
#define MAP_INC_82 83
#define MAP_INC_83 84
#define MAP_INC_84 85
#define MAP_INC_85 86
#define MAP_INC_86 87
#define MAP_INC_87 88
#define MAP_INC_88 89
#define MAP_INC_89 90
#define MAP_INC_90 91
#define MAP_INC_91 92
#define MAP_INC_92 93
#define MAP_INC_93 94
#define MAP_INC_94 95
#define MAP_INC_95 96
#define MAP_INC_96 97
#define MAP_INC_97 98
#define MAP_INC_98 99
#define MAP_INC_99 100
#define MAP_INC_100 101
#define MAP_INC_101 102
#define MAP_INC_102 103
#define MAP_INC_103 104
#define MAP_INC_104 105
#define MAP_INC_105 106
#define MAP_INC_106 107
#define MAP_INC_107 108
#define MAP_INC_108 109
#define MAP_INC_109 110
#define MAP_INC_110 111
#define MAP_INC_111 112
#define MAP_INC_112 113
#define MAP_INC_113 114
#define MAP_INC_114 115
#define MAP_INC_115 116
#define MAP_INC_116 117
#define MAP_INC_117 118
#define MAP_INC_118 119
#define MAP_INC_119 120
#define MAP_INC_120 121
#define MAP_INC_121 122
#define MAP_INC_122 123
#define MAP_INC_123 124
#define MAP_INC_124 125
#define MAP_INC_125 126
#define MAP_INC_126 127
#define MAP_INC_127 128
#define MAP_INC_128 129
#define MAP_INC_129 130
#define MAP_INC_130 131
#define MAP_INC_131 132
#define MAP_INC_132 133
#define MAP_INC_133 134
#define MAP_INC_134 135
#define MAP_INC_135 136
#define MAP_INC_136 137
#define MAP_INC_137 138
#define MAP_INC_138 139
#define MAP_INC_139 140
#define MAP_INC_140 141
#define MAP_INC_141 142
#define MAP_INC_142 143
#define MAP_INC_143 144
#define MAP_INC_144 145
#define MAP_INC_145 146
#define MAP_INC_146 147
#define MAP_INC_147 148
#define MAP_INC_148 149
#define MAP_INC_149 150
#define MAP_INC_150 151
#define MAP_INC_151 152
#define MAP_INC_152 153
#define MAP_INC_153 154
#define MAP_INC_154 155
#define MAP_INC_155 156
#define MAP_INC_156 157
#define MAP_INC_157 158
#define MAP_INC_158 159
#define MAP_INC_159 160
#define MAP_INC_160 161
#define MAP_INC_161 162
#define MAP_INC_162 163
#define MAP_INC_163 164
#define MAP_INC_164 165
#define MAP_INC_165 166
#define MAP_INC_166 167
#define MAP_INC_167 168
#define MAP_INC_168 169
#define MAP_INC_169 170
#define MAP_INC_170 171
#define MAP_INC_171 172
#define MAP_INC_172 173
#define MAP_INC_173 174
#define MAP_INC_174 175
#define MAP_INC_175 176
#define MAP_INC_176 177
#define MAP_INC_177 178
#define MAP_INC_178 179
#define MAP_INC_179 180
#define MAP_INC_180 181
#define MAP_INC_181 182
#define MAP_INC_182 183
#define MAP_INC_183 184
#define MAP_INC_184 185
#define MAP_INC_185 186
#define MAP_INC_186 187
#define MAP_INC_187 188
#define MAP_INC_188 189
#define MAP_INC_189 190
#define MAP_INC_190 191
#define MAP_INC_191 192
#define MAP_INC_192 193
#define MAP_INC_193 194
#define MAP_INC_194 195
#define MAP_INC_195 196
#define MAP_INC_196 197
#define MAP_INC_197 198
#define MAP_INC_198 199
#define MAP_INC_199 200
#define MAP_INC_200 201
#define MAP_INC_201 202
#define MAP_INC_202 203
#define MAP_INC_203 204
#define MAP_INC_204 205
#define MAP_INC_205 206
#define MAP_INC_206 207
#define MAP_INC_207 208
#define MAP_INC_208 209
#define MAP_INC_209 210
#define MAP_INC_210 211
#define MAP_INC_211 212
#define MAP_INC_212 213
#define MAP_INC_213 214
#define MAP_INC_214 215
#define MAP_INC_215 216
#define MAP_INC_216 217
#define MAP_INC_217 218
#define MAP_INC_218 219
#define MAP_INC_219 220
#define MAP_INC_220 221
#define MAP_INC_221 222
#define MAP_INC_222 223
#define MAP_INC_223 224
#define MAP_INC_224 225
#define MAP_INC_225 226
#define MAP_INC_226 227
#define MAP_INC_227 228
#define MAP_INC_228 229
#define MAP_INC_229 230
#define MAP_INC_230 231
#define MAP_INC_231 232
#define MAP_INC_232 233
#define MAP_INC_233 234
#define MAP_INC_234 235
#define MAP_INC_235 236
#define MAP_INC_236 237
#define MAP_INC_237 238
#define MAP_INC_238 239
#define MAP_INC_239 240
#define MAP_INC_240 241
#define MAP_INC_241 242
#define MAP_INC_242 243
#define MAP_INC_243 244
#define MAP_INC_244 245
#define MAP_INC_245 246
#define MAP_INC_246 247
#define MAP_INC_247 248
#define MAP_INC_248 249
#define MAP_INC_249 250
#define MAP_INC_250 251
#define MAP_INC_251 252
#define MAP_INC_252 253
#define MAP_INC_253 254
#define MAP_INC_254 255
#define MAP_INC_255 256
#define MAP_INC_256 257
#define MAP_INC_257 258
#define MAP_INC_258 259
#define MAP_INC_259 260
#define MAP_INC_260 261
#define MAP_INC_261 262
#define MAP_INC_262 263
#define MAP_INC_263 264
#define MAP_INC_264 265
#define MAP_INC_265 266
#define MAP_INC_266 267
#define MAP_INC_267 268
#define MAP_INC_268 269
#define MAP_INC_269 270
#define MAP_INC_270 271
#define MAP_INC_271 272
#define MAP_INC_272 273
#define MAP_INC_273 274
#define MAP_INC_274 275
#define MAP_INC_275 276
#define MAP_INC_276 277
#define MAP_INC_277 278
#define MAP_INC_278 279
#define MAP_INC_279 280
#define MAP_INC_280 281
#define MAP_INC_281 282
#define MAP_INC_282 283
#define MAP_INC_283 284
#define MAP_INC_284 285
#define MAP_INC_285 286
#define MAP_INC_286 287
#define MAP_INC_287 288
#define MAP_INC_288 289
#define MAP_INC_289 290
#define MAP_INC_290 291
#define MAP_INC_291 292
#define MAP_INC_292 293
#define MAP_INC_293 294
#define MAP_INC_294 295
#define MAP_INC_295 296
#define MAP_INC_296 297
#define MAP_INC_297 298
#define MAP_INC_298 299
#define MAP_INC_299 300
#define MAP_INC_300 301
#define MAP_INC_301 302
#define MAP_INC_302 303
#define MAP_INC_303 304
#define MAP_INC_304 305
#define MAP_INC_305 306
#define MAP_INC_306 307
#define MAP_INC_307 308
#define MAP_INC_308 309
#define MAP_INC_309 310
#define MAP_INC_310 311
#define MAP_INC_311 312
#define MAP_INC_312 313
#define MAP_INC_313 314
#define MAP_INC_314 315
#define MAP_INC_315 316
#define MAP_INC_316 317
#define MAP_INC_317 318
#define MAP_INC_318 319
#define MAP_INC_319 320
#define MAP_INC_320 321
#define MAP_INC_321 322
#define MAP_INC_322 323
#define MAP_INC_323 324
#define MAP_INC_324 325
#define MAP_INC_325 326
#define MAP_INC_326 327
#define MAP_INC_327 328
#define MAP_INC_328 329
#define MAP_INC_329 330
#define MAP_INC_330 331
#define MAP_INC_331 332
#define MAP_INC_332 333
#define MAP_INC_333 334
#define MAP_INC_334 335
#define MAP_INC_335 336
#define MAP_INC_336 337
#define MAP_INC_337 338
#define MAP_INC_338 339
#define MAP_INC_339 340
#define MAP_INC_340 341
#define MAP_INC_341 342
#define MAP_INC_342 343
#define MAP_INC_343 344
#define MAP_INC_344 345
#define MAP_INC_345 346
#define MAP_INC_346 347
#define MAP_INC_347 348
#define MAP_INC_348 349
#define MAP_INC_349 350
#define MAP_INC_350 351
#define MAP_INC_351 352
#define MAP_INC_352 353
#define MAP_INC_353 354
#define MAP_INC_354 355
#define MAP_INC_355 356
#define MAP_INC_356 357
#define MAP_INC_357 358
#define MAP_INC_358 359
#define MAP_INC_359 360
#define MAP_INC_360 361
#define MAP_INC_361 362
#define MAP_INC_362 363
#define MAP_INC_363 364
#define MAP_INC_364 365
#define MAP_INC_365 366
// #include <engine/meta/RTTI.hpp>

// #include <engine/pool/ComponentArray.hpp>

#include <array>
// #include <engine/ecs/Entity.hpp>

// #include <engine/pool/Pool.hpp>

// #include <engine/meta/Log.hpp>

// #include <engine/pool/IPool.hpp>

class IPool {
 public:
  virtual ~IPool() = default;

  virtual void Allocate(const Entity& e) = 0;
  virtual void Free(const Entity& e) = 0;
  virtual void* Get(const Entity& e) = 0;
};
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

/**
 * @brief Une Pool alloue des objets pour une utilisation ultérieure
 */
template <typename T>
class Pool {
 public:
  /**
   * @brief Les PoolItem stockent chaque élément d'une arène
   * On définie un union pour partager l'espace
   */
  union PoolItem {
   public:
    // Methods for the list of free items.
    PoolItem* get_next_item() const { return next; }
    void set_next_item(PoolItem* n) { next = n; }

    // Methods for the storage of the item.
    T* get_storage() { return reinterpret_cast<T*>(&datum); }

    // Given a T* cast it to a PoolItem*
    static PoolItem* storage_to_item(T* t) {
      PoolItem* current_item = reinterpret_cast<PoolItem*>(t);
      return current_item;
    }

   private:
    using StorageType = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

    // Points to the next freely available item.
    PoolItem* next;

    // Storage of the item. Note that this is a union
    // so it is shared with the pointer "next" above.
    StorageType datum;
  };

  class Arena {
   public:
    /**
     * @brief Le constructeur alloue un table de PoolItem, de taille arena_size
     */
    explicit Arena(size_t arena_size) : storage(new PoolItem[arena_size]) {
      if (arena_size <= 0) {
        throw std::invalid_argument("Arena size must be positive");
      }

      for (size_t i = 1; i < arena_size; i++) {
        // Set the "next" pointer of each item
        storage[i - 1].set_next_item(&storage[i]);
      }
      // Last "next" pointer of the storage is null
      storage[arena_size - 1].set_next_item(nullptr);
    }

    // Returns a pointer to the array of items. This is used by the arena
    // itself. This is only used to update free_list during initialization
    // or when creating a new arena when the current one is full.
    PoolItem* get_storage() const { return storage.get(); }

   private:
    std::unique_ptr<PoolItem[]> storage;  // Storage of this arena.
  };

  /**
   * @brief Crée une nouvelle Pool qui utilisera des Arena de arena_size
   */
  explicit Pool(size_t arena_size)
      : arena_size(arena_size), arena(new Arena(arena_size)), free_list(arena->get_storage()) {}

  /**
   * @brief Au moment de la destruction de la Pool, on va libéré toute les
   * valeurs qui y sont stocké
   */
  ~Pool() {
    PoolItem* s = arena->get_storage();
    for (unsigned int i = 0; i < arena_size; ++i) {
      free((s + i)->get_storage());
    }
  }

  /**
   * @brief Alloue un objet dans l'arène
   * @return Pointeur vers l'objet alloué
   */
  template <typename... Args>
  T* alloc(Args&&... args) {
    assert(free_list != nullptr && "Unable to get more object from the pool, Arena is full.");

    // Get the first free item.
    PoolItem* current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->get_next_item();

    return set_storage(current_item, std::forward<Args>(args)...);
  }

  /**
   * @brief Libère un objet dans l'arène
   */
  void free(T* t) {
    // Destroy the object.
    t->T::~T();

    // Convert this pointer to T to its enclosing pointer of an item of the
    // arena.
    PoolItem* current_item = PoolItem::storage_to_item(t);

    // Add the item at the beginning of the free list.
    current_item->set_next_item(free_list);
    free_list = current_item;
  }

  typedef PoolItem* iterator;

  iterator begin() {
    PoolItem* current_item = arena->get_storage();
    if (in_free_list(current_item)) return next(current_item);
    return current_item;
  }

  iterator end() { return begin() + arena_size; }

  // TODO : we can override operator++
  iterator next(iterator item) {
    PoolItem* current_item = item->get_next_item();
    if (current_item == nullptr) return end();

    while (in_free_list(current_item)) {
      current_item = current_item->get_next_item();
      if (current_item == nullptr) return end();
    }

    return current_item;
  }

  PoolItem* at(const uint32_t& id) {
    assert(id < arena_size && "Pool out of range.");
    return arena->get_storage() + id;
  }

  PoolItem* at(const uint32_t& id) const { return this->at(id); }

 private:
  // Size of the arenas created by the pool.
  size_t arena_size;

  // Current arena. Changes when it becomes full and we want to allocate one
  // more object.
  std::unique_ptr<Arena> arena;

  // List of free elements. The list can be threaded between different arenas
  // depending on the deallocation pattern.
  PoolItem* free_list;

  template <typename... Args>
  T* set_storage(PoolItem* current_item, Args&&... args) {
    // Get the storage for T.
    T* result = current_item->get_storage();

    // Construct the object in the obtained storage.
    new (result) T(std::forward<Args>(args)...);

    return result;
  }
};

template <typename T>
class ComponentArray : public IPool {
 public:
  void Allocate(const Entity& entity) {
    if (entity < MAX_ENTITIES && !componentIsSet[entity]) {
      // datnum[entity] = T();
      componentIsSet[entity] = true;
    }
  }

  void Free(const Entity& entity) {
    if (entity < MAX_ENTITIES && componentIsSet[entity]) {
      datnum[entity].T::~T();
      componentIsSet[entity] = false;
    }
  }

  void* Get(const Entity& entity) {
    if (componentIsSet[entity])
      return &(datnum[entity]);
    else
      return nullptr;
  }

 private:
  std::array<T, MAX_ENTITIES> datnum;
  std::array<bool, MAX_ENTITIES> componentIsSet;
};
#include <map>
#include <memory>
#include <string>

// All Engine's IComponent
#define COMPONENTS Transform, RectRenderer, CircleRenderer, RectCollider, Velocity

// Register a IComponent
#define REGISTER_COMPONENT(klass) Registry::GetInstance()->RegisterComponent<klass>();

// Register all IComponent
#define REGISTER_COMPONENTS MAP(REGISTER_COMPONENT, COMPONENTS)

/**
 * @brief Permet de gérer l'allocation/libération des IComponent
 */
class ComponentFactory {
 public:
  /**
   * @brief On alloue un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Allocate(const RTTI& rtti, const Entity& entity) {
    it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() && "We cannot allocate a unknow Component.");
    it->second->Allocate(entity);
  }

  /**
   * @brief On libère un IComponent associé a une Entity
   * @param rtti Est l'identifiant du IComponent à supprimer
   * @param entity Est l'Entity qui possède le IComponent à supprimé
   */
  void Free(const RTTI& rtti, const Entity& entity) {
    it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() && "We cannot free a unknow Component.");
    it->second->Free(entity);
  }

  /**
   * @brief On libère tout les IComponent associé a une Entity
   * @param entity Est l'Entity qui possède les IComponent à supprimés
   */
  void FreeEntity(const Entity& entity) {
    for (auto const& x : componentArrays) {
      Free(x.first, entity);
    }
  }

  /**
   * @brief On enregistre le IComponent est on crée une Pool associé
   */
  template <typename T>
  void Register() {
    const RTTI& rtti = T::rtti;

    assert(componentArrays.find(rtti) == componentArrays.end() &&
           "Registering component type more than once.");

    componentArrays.insert({rtti, std::make_shared<ComponentArray<T>>()});
  }

  /**
   * @brief Permet de récupèrer le IComponent d'une Entity
   * @param entity L'Entity qui possède le IComponent que l'on veut récupèrer
   * @return Le pointeur vers le IComponent de l'Entity, si il n'existe pas,
   * retourne nullptr
   */
  template <typename T>
  T* Get(const Entity& entity) const {
    auto pool = GetComponentPool<T>().get();
    return reinterpret_cast<T*>(pool->Get(entity));
  }

  /**
   * @brief Permet de savoir si une Entity possède certains IComponent
   * @param entity L'Entity qui possède les IComponent
   * @param args Les différents RTTI des IComponent que l'on veut tester
   * @return Retourne vraie si l'entité possède tout les IComponent
   */
  template <typename... Args>
  bool Has(const Entity& entity, Args&&... args) const {
    bool result = true;
    auto check_has = [&](auto& arg) {
      result &= (componentArrays.at(arg)->Get(entity) != nullptr);
    };
    (check_has(args), ...);
    return result;
  }

 private:
  using it_comp_t = std::map<RTTI, std::shared_ptr<IPool>>::iterator;
  using const_it_comp_t = std::map<RTTI, std::shared_ptr<IPool>>::const_iterator;

  std::map<RTTI, std::shared_ptr<IPool>> componentArrays;  // Map de l'id d'un IComponent vers une
                                                           // Pool de IComponent

  /**
   * @brief Permet d'obtenir pointeur de la Pool de type T
   * @return Le pointeur de la Pool T
   */
  template <typename T>
  std::shared_ptr<ComponentArray<T>> GetComponentPool() const {
    const RTTI& rtti = T::rtti;

    const_it_comp_t it = componentArrays.find(rtti);
    assert(it != componentArrays.end() && "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(it->second);
  }
};
// #include <engine/factory/EntityFactory.hpp>

#include <any>
#include <array>
#include <cassert>
// #include <engine/ecs/Entity.hpp>

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

class Registry;

/**
 * @brief Permet de gérer l'allocation/libération des Entity
 */
class EntityFactory {
 public:
  /**
   * @brief Initialise la queue avec toute les Entity possible
   */
  EntityFactory() : livingEntityCount(0) {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
      availableEntities.push(entity);
      entityIsSet[entity] = false;
    }
  }

  /**
   * @brief Ajoute d'une Entity
   * @return L'identifiant de l'Entity
   */
  Entity Allocate() {
    assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;

    entityIsSet[id] = true;

    return id;
  }

  /**
   * @brief Supprime l'Entity
   */
  void Free(const Entity& entity) {
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    availableEntities.push(entity);
    --livingEntityCount;

    entityIsSet[entity] = false;
  }

  /**
   * @brief Indique si l'Entity correspondante est créé
   * @return Retourne vrai si l'Entity est créé
   */
  bool IsSet(const Entity& entity) const { return entityIsSet[entity]; }

 private:
  std::array<bool, MAX_ENTITIES> entityIsSet;
  std::queue<Entity> availableEntities{};  // Queue des Entity disponibles
  uint32_t livingEntityCount{};            // Total des Entity en "vie"
};
// #include <engine/factory/Registry.hpp>

// #include <engine/async/ThreadPool.hpp>

#include <functional>
#include <future>
#include <memory>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class ThreadPool {
 private:
  std::vector<std::thread> workers;                    // Liste de nos threads (pour les join)
  std::queue<std::function<void()>> m_function_queue;  // Queue des taches

  // Synchronization
  std::mutex m_lock;
  std::condition_variable m_data_condition;
  std::atomic<bool> m_accept_functions;

 public:
  /**
   * @brief Le constructeur démarre un certain nombre de thread (workers)
   */
  explicit ThreadPool(size_t threads) : m_accept_functions(true) {
    for (size_t i = 0; i < threads; ++i)
      workers.emplace_back([this] {
        while (true) {
          std::function<void()> func;

          {
            // Le mutex sera déverrouillé, en sortant du scope, car le
            // desctuteur du lock sera appelé (RAII)
            std::unique_lock<std::mutex> lock(this->m_lock);
            this->m_data_condition.wait(lock, [this] {
              return !this->m_accept_functions || !this->m_function_queue.empty();
            });
            if (!this->m_accept_functions && this->m_function_queue.empty()) {
              // lock will be release automatically.
              // finish the thread loop and let it join in the main thread.
              return;
            }
            func = std::move(this->m_function_queue.front());
            this->m_function_queue.pop();
          }

          func();
        }
      });
  }

  /**
   * @brief Le destructeur join tout les threads
   */
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(m_lock);
      m_accept_functions = false;
    }
    m_data_condition.notify_all();
    for (std::thread& worker : workers) worker.join();
  }

  /**
   * @brief Permet d'ajouter une nouvelle tache à la ThreadPool
   */
  template <class F, class... Args>
  auto push(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto func = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = func->get_future();
    {
      std::unique_lock<std::mutex> lock(m_lock);

      // On bloque l'ajout de nouvelle tache, après avoir stoper la ThreadPool
      if (!m_accept_functions)
        throw std::runtime_error("ThreadPool is stopped, you cannot push new task!");

      m_function_queue.emplace([func]() { (*func)(); });
    }
    m_data_condition.notify_one();
    return res;
  }
};

// #include <engine/factory/ComponentFactory.hpp>

// #include <engine/factory/EntityFactory.hpp>

// #include <engine/factory/SystemFactory.hpp>

#include <cstdint>
// #include <engine/ecs/ISystem.hpp>

// #include <engine/meta/RTTI.hpp>

/**
 * @brief ISystem is a pure interface
 */
class ISystem {
 public:
  RTTI_DEFINITION_BASE(ISystem)
  virtual void update() const = 0;
  virtual ~ISystem() = default;
};
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

class LogicalSystem;
class PhysicalSystem;
class RendererSystem;

// All Engine's ISystem
#define SYSTEMS LogicalSystem, PhysicalSystem, RendererSystem

// Register a ISystem
#define REGISTER_SYSTEM(klass) Registry::GetInstance()->RegisterSystem<klass>();

// Register all ISystem
#define REGISTER_SYSTEMS MAP(REGISTER_SYSTEM, SYSTEMS)

class SystemFactory {
 public:
  SystemFactory() : engineSystems(3) {}

  template <typename T>
  T* Register() {
    if constexpr (std::is_same_v<T, LogicalSystem>) {
      engineSystems[0] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[0].get());
    } else if constexpr (std::is_same_v<T, PhysicalSystem>) {
      engineSystems[1] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[1].get());
    } else if constexpr (std::is_same_v<T, RendererSystem>) {
      engineSystems[2] = std::make_shared<T>();
      return reinterpret_cast<T*>(engineSystems[2].get());
    } else {
      const RTTI& id = T::rtti;

      if (systems.find(id) == systems.end()) {
        systems.insert({id, std::make_shared<T>()});
      }

      return reinterpret_cast<T*>(systems[id].get());
    }
    return nullptr;
  }

  void Update() {
    // On update d'abord les ISystem rajoutés
    for (auto const& x : systems) {
      x.second->update();
    }

    // Puis ensuite les ISystem de l'Engine
    engineSystems[0]->update();
    engineSystems[1]->update();
    // systems[RendererSystem::rtti]->update();

    // TODO : faire un système de dépendance entre les systèmes pour pouvoir
    // choisir l'ordre
  }

  void Render() { engineSystems[2]->update(); }

 private:
  std::map<const RTTI, std::shared_ptr<ISystem>> systems{};
  std::vector<std::shared_ptr<ISystem>> engineSystems;
};
// #include <engine/meta/RTTI.hpp>

// #include <engine/meta/Singleton.hpp>

#include <map>
#include <memory>
#include <utility>
#include <vector>

/**
 * @brief Le Registry permet de gérer les données du jeu
 */
class Registry : public Singleton<Registry> {
  // needs to be friend in order to
  // access the private constructor/destructor
  friend class Singleton<Registry>;

 public:
  /**
   * @brief Permet d'allouer un IComponent
   * cf. ComponentFactory
   */
  void AllocateComponent(const RTTI& rtti, const Entity& entity) {
    compFact->Allocate(rtti, entity);
  }

  /**
   * @brief Permet de libérer un IComponent
   * cf. ComponentFactory
   */
  void FreeComponent(const RTTI& rtti, const Entity& entity) { compFact->Free(rtti, entity); }

  /**
   * @brief Permet d'enregistrer un IComponent dans la ComponentFactory
   * cf. ComponentFactory
   */
  template <typename T>
  void RegisterComponent() {
    compFact->Register<T>();
  }

  /**
   * @brief Permet de récupèrer le IComponent d'une Entity
   */
  template <typename T>
  T* GetComponent(const Entity& entity) {
    return compFact->Get<T>(entity);
  }

  /**
   * @brief Permet de construire une Entity, alloue tout les IComponent et
   * retourne une Entity nous utilisée
   * @param args Liste des arguments, normalement RTTI de IComponent
   * @return Retourne la nouvelle Entity
   */
  template <typename... Args>
  Entity AllocateEntity(Args&&... args) {
    const Entity& id = entiFact->Allocate();

    // clang-format off
    auto allocate = [&](auto &arg) { AllocateComponent(arg, id); };
    (allocate(args), ...);
    // clang-format on

    return id;
  }

  /**
   * @brief Permet de libérer une Entity
   */
  void FreeEntity(const Entity& entity) {
    compFact->FreeEntity(entity);
    entiFact->Free(entity);
  }

  /**
   * @brief Permet de récupèrer une liste d'Entity possèdant tous certains
   * IComponent
   * @param entities Réfèrence vers la liste d'Entity (d'un ISystem), que l'on
   * rempli
   * @param args Liste des arguments, normalement RTTI de IComponent
   */
  template <typename... Args>
  void GetEntitiesWithTags(std::vector<Entity>& entities, Args&&... args) const {
    int idx = 0;
    entities.resize(MAX_ENTITIES);

    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
      if (!entiFact->IsSet(entity)) continue;
      if (compFact->Has(entity, std::forward<Args>(args)...)) {
        entities[idx] = entity;
        idx++;
      }
    }

    entities.resize(idx);  // Normalement pas d'allocation car la taille max est
                           // déjà réservé
  }

  /**
   * @brief Permet d'enregistrer un ISystem dans la SystemFactory
   */
  template <typename T>
  T* RegisterSystem() {
    return systFact->Register<T>();
  }

  /**
   * @brief Permet d'update les ISystem
   */
  void UpdateSystem() { systFact->Update(); }
  void RenderSystem() { systFact->Render(); }

  const size_t numThreads;
  ThreadPool threadPool;
  std::vector<Entity> entitiesQuery;
  std::vector<std::future<void>> results;

 private:
  /**
   * @brief Initalise le Registry en créant une ComponentFactory et une
   * EntityFactory
   */
  Registry()
      : numThreads(1),  // std::thread::hardware_concurrency()),
        threadPool(numThreads),
        entitiesQuery(MAX_ENTITIES),
        results(MAX_ENTITIES) {
    compFact = std::make_unique<ComponentFactory>();
    entiFact = std::make_unique<EntityFactory>();
    systFact = std::make_unique<SystemFactory>();
  }
  ~Registry() {}

  std::unique_ptr<ComponentFactory> compFact;
  std::unique_ptr<EntityFactory> entiFact;
  std::unique_ptr<SystemFactory> systFact;
};
// #include <engine/factory/SystemFactory.hpp>

// #include <engine/meta/Log.hpp>

// #include <engine/system/LogicalSystem.hpp>

// #include <engine/ecs/Entity.hpp>

// #include <engine/ecs/ISystem.hpp>

#include <vector>

class LogicalSystem : public ISystem {
 public:
  RTTI_DEFINITION(LogicalSystem, ISystem)
  ~LogicalSystem() {}

  void update() const {
    LOG(LOG_INFO, "[LogicalSystem] Update!");
    /**
     * @todo Mettre ici la logique: comportements, déplacements, animations
     * etc... Certains objets doivent toujours être updaté tandis que d’autres
     * sont en pause lorsqu’ils sont trop éloignés.
     */
  }
};
// #include <engine/system/PhysicalSystem.hpp>

#include <SDL_rect.h>

// #include <engine/component/collider/RectCollider.hpp>

// #include <engine/component/Transform.hpp>

// #include <engine/ecs/ISystem.hpp>

// #include <engine/event/Collide.hpp>

// #include <engine/event/IEvent.hpp>

// #include <engine/meta/RTTI.hpp>

class IEvent {
 public:
  RTTI_DEFINITION_BASE(IEvent)
};

class Collide final : public IEvent {
 public:
  RTTI_DEFINITION(Collide, IEvent)

  inline Collide(const Entity& e1, const Entity& e2) : e1(e1), e2(e2) {}
  inline const Entity& entity1() const { return e1; }
  inline const Entity& entity2() const { return e2; }

 private:
  const Entity& e1;
  const Entity& e2;
};
// #include <engine/event/Dispatcher.hpp>

// #include <engine/event/EventCallback.hpp>

// #include <engine/event/IEvent.hpp>

class IEventCallback {
 public:
  virtual void Trigger(const IEvent&) = 0;
};

template <typename T, typename E>
class EventCallback : public IEventCallback {
 public:
  EventCallback(T* instance, void (T::*function)(E*)) : instance(instance), function(function) {}

  void Trigger(const IEvent& event) { (instance->*function)((E*)(&event)); }

 private:
  T* instance;
  void (T::*function)(E*);
};
// #include <engine/event/IEvent.hpp>

// #include <engine/meta/RTTI.hpp>

// #include <engine/meta/Singleton.hpp>

#include <map>
#include <memory>

class Dispatcher : public Singleton<Dispatcher> {
  friend class Singleton<Dispatcher>;

 public:
  template <typename T, typename E>
  void RegisterAction(T* instance, void (T::*function)(E*)) {
    const RTTI& id = E::rtti;

    if (inputEvents.find(id) == inputEvents.end()) {
      inputEvents.insert({id, std::make_shared<EventCallback<T, E>>(instance, function)});
    }
  }

  template <typename T>
  void Trigger(const T& event) {
    const RTTI& id = T::rtti;

    if (inputEvents.find(id) != inputEvents.end()) {
      inputEvents[id]->Trigger(event);
    }
  }

 private:
  Dispatcher() {}
  ~Dispatcher() {}

  std::map<RTTI, std::shared_ptr<IEventCallback>> inputEvents;
};
// #include <engine/factory/Registry.hpp>

class PhysicalSystem : public ISystem {
 public:
  RTTI_DEFINITION(PhysicalSystem, ISystem)
  ~PhysicalSystem() {}

  void update() const {
    LOG(LOG_INFO, "[PhysicalSystem] Update!");
    /**
     * @todo Mettre ici la simulation physique: détection de collisions,
     * résolution des pénétrations et des interactions. Les objets éloignés ou
     * qui ne subissent pas de force ou restitution sont endormis.
     */

    Registry* registry = Registry::GetInstance();
    registry->GetEntitiesWithTags(registry->entitiesQuery, RectCollider::rtti);

    registry->results.resize(registry->entitiesQuery.size() - 1);
    for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
      for (unsigned int j = i + 1; j < registry->entitiesQuery.size(); j++) {
        registry->results[i] = registry->threadPool.push(
            [](const Entity& e1, const Entity& e2) {
              //
              // Begin Intersection Between Two Rect
              Registry* registry = Registry::GetInstance();

              Transform* trans1 = registry->GetComponent<Transform>(e1);
              Transform* trans2 = registry->GetComponent<Transform>(e2);

              if (trans1->intersect(*trans2)) {
                Dispatcher* dispatcher = Dispatcher::GetInstance();
                dispatcher->Trigger(Collide(e1, e2));
              }
              // End
              //
            },
            registry->entitiesQuery[i], registry->entitiesQuery[j]);
      }
    }

    for (auto&& result : registry->results) result.get();
  }
};
// #include <engine/system/RendererSystem.hpp>

#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

// #include <engine/component/renderer/CircleRenderer.hpp>

// #include <engine/component/renderer/RectRenderer.hpp>

// #include <engine/core/Context.hpp>

// #include <engine/core/Window.hpp>

// #include <engine/ecs/ISystem.hpp>

// #include <engine/meta/Log.hpp>

class RendererSystem : public ISystem {
 public:
  RTTI_DEFINITION(RendererSystem, ISystem)
  ~RendererSystem() {}

  void update() const {
    LOG(LOG_INFO, "[RendererSystem] Update!");
    /**
     * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être
     * affiché. Attention il faut parfois aussi tenir compte des objets hors
     * champs (ombres et lumières, partiellement visibles...)
     */

    Context* context = Context::GetInstance();

    // Flush renderer.
    SDL_SetRenderDrawColor(context->window()->renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->window()->renderer());

    Registry* registry = Registry::GetInstance();

    // *** RectRenderer ***
    {
      registry->GetEntitiesWithTags(registry->entitiesQuery, RectRenderer::rtti);

      registry->results.resize(registry->entitiesQuery.size());
      for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
        registry->results[i] = registry->threadPool.push(
            [&](const Entity& entity) {
              const Transform* const trans = registry->GetComponent<Transform>(entity);

              float x = trans->x();
              float y = trans->y();
              float4 size = trans->size();

              // First we set the rectangle fill colour to that of the spritecomponents.
              SDL_SetRenderDrawColor(context->window()->renderer(), 255.f, 255.f, 255.f, 255.f);

              // Then we create the actual rectangle.
              const SDL_Rect draw_rect = {x, y, size.x, size.y};

              // Now the rectangle gets renderered with the appropriate colours and position
              // data to the window.
              SDL_RenderFillRect(context->window()->renderer(), &draw_rect);
            },
            registry->entitiesQuery[i]);
      }
    }

    // *** CircleRenderer ***
    {
      registry->GetEntitiesWithTags(registry->entitiesQuery, CircleRenderer::rtti);

      registry->results.resize(registry->entitiesQuery.size());
      for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
        registry->results[i] = registry->threadPool.push(
            [&](const Entity& entity) {
              const Transform* const trans = registry->GetComponent<Transform>(entity);

              float x = trans->x();
              float y = trans->y();
              float4 size = trans->size();

              // We use SDL2_gfx to make drawing circles easier.
              filledCircleRGBA(context->window()->renderer(), x, y, size.x, 255.f, 255.f, 255.f,
                               255.f);
            },
            registry->entitiesQuery[i]);
      }
    }

    for (auto&& result : registry->results) result.get();

    // Draw everything.
    SDL_RenderPresent(context->window()->renderer());
  }
};
#include <memory>
#include <vector>

class Engine {
 public:
  void FixedUpdate() const {
    LOG(LOG_INFO, "[Engine] Update!");

    // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl
    // operates on milliseconds not nanoseconds.
    const constexpr double dt = 1000.0 / 60.0;

    Context* context = Context::GetInstance();
    Registry* registry = Registry::GetInstance();

    // This is a fixed-step gameloop
    while (context->clock()->deltaTime() >= dt) {
      registry->UpdateSystem();
      context->clock()->Increment(dt);
    }
  }

  void Render() const {
    LOG(LOG_INFO, "[Engine] Render!");

    Registry* registry = Registry::GetInstance();
    registry->RenderSystem();
  }
};
// #include <engine/core/Input.hpp>

#include <SDL2/SDL_events.h>

// #include <engine/core/Context.hpp>

// #include <engine/core/Window.hpp>

// #include <engine/event/KeyDown.hpp>

// #include <engine/event/IEventKey.hpp>

// #include <engine/event/IEvent.hpp>

// #include <engine/meta/RTTI.hpp>

class IEventKey : public IEvent {
 public:
  RTTI_DEFINITION(IEventKey, IEvent)

  virtual inline int key() const = 0;
};

class KeyDown final : public IEventKey {
 public:
  RTTI_DEFINITION(KeyDown, IEventKey)

  inline KeyDown(int key_code) : key_code(key_code) {}
  inline int key() const { return key_code; }

 private:
  int key_code = -1;
};
// #include <engine/event/KeyUp.hpp>

// #include <engine/event/IEventKey.hpp>

class KeyUp final : public IEventKey {
 public:
  RTTI_DEFINITION(KeyUp, IEventKey)

  inline KeyUp(int key_code) : key_code(key_code) {}
  inline int key() const { return key_code; }

 private:
  int key_code = -1;
};
// #include <engine/event/Dispatcher.hpp>

class Context;

class Input {
 public:
  void Update() const {
    Dispatcher* dispatcher = Dispatcher::GetInstance();
    Context* context = Context::GetInstance();

    Window* window = context->window();
    SDL_Event& event = window->m_event;

    // Process all user and system events.
    while (SDL_PollEvent(&event) != 0) {
      // https://wiki.libsdl.org/SDL_Event
      switch (event.type) {
        case SDL_QUIT:
          window->close();
          break;

        case SDL_KEYDOWN: {
          SDL_Keycode& sym = event.key.keysym.sym;
          if (sym == SDLK_ESCAPE) {
            window->close();
          } else {
            dispatcher->Trigger(KeyDown(sym));
          }
        } break;

        case SDL_KEYUP: {
          SDL_Keycode& sym = event.key.keysym.sym;
          dispatcher->Trigger(KeyUp(sym));
        } break;
      }
    }
  }
};
// #include <engine/ecs/IComponent.hpp>

// #include <engine/ecs/ISystem.hpp>

// #include <engine/factory/EntityFactory.hpp>

// #include <engine/factory/Registry.hpp>

// #include <engine/factory/SystemFactory.hpp>

// #include <engine/meta/Log.hpp>

// #include <engine/system/LogicalSystem.hpp>

// #include <engine/system/PhysicalSystem.hpp>

// #include <engine/system/RendererSystem.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <thread>

class Game {
 public:
  Game(std::string title, const int w, const int h, std::uint32_t flags) {
    // Setup SDL2 and stuff.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
      throw_sdl2_exception("Failed to init SDL2.");
    }

    Context* context = Context::GetInstance();
    context->window()->create(title, w, h, flags);
  }

  ~Game() noexcept { SDL_Quit(); }

  void run(const std::shared_ptr<Scene>& scene) {
    try {
      scene->preload();

      // On enregistre tout les IComponent et tout les ISystem
      REGISTER_COMPONENTS
      REGISTER_SYSTEMS

      scene->create();

      Context* context = Context::GetInstance();
      context->clock()->Initialize();

      int frameIndex = 0;
      while (context->window()->is_open()) {
        LOG(LOG_INFO, "[Game] frame # " << frameIndex);

        context->clock()->Update();
        context->input()->Update();

        context->engine()->FixedUpdate();
        context->engine()->Render();

        frameIndex++;
      }
    } catch (const std::exception& e) {
      LOG(LOG_ERROR, e.what());
    }
  }
};
// #include <engine/Scene.hpp>

// #include <engine/async/ThreadPool.hpp>

// #include <engine/component/renderer/RectRenderer.hpp>

// #include <engine/component/renderer/CircleRenderer.hpp>

// #include <engine/component/collider/RectCollider.hpp>

// #include <engine/component/Transform.hpp>

// #include <engine/component/Velocity.hpp>

// #include <engine/core/Clock.hpp>

// #include <engine/core/Context.hpp>

// #include <engine/core/Engine.hpp>

// #include <engine/core/Input.hpp>

// #include <engine/core/Window.hpp>

// #include <engine/ecs/Entity.hpp>

// #include <engine/ecs/IComponent.hpp>

// #include <engine/ecs/ISystem.hpp>

// #include <engine/event/Collide.hpp>

// #include <engine/event/EventCallback.hpp>

// #include <engine/event/IEvent.hpp>

// #include <engine/event/IEventKey.hpp>

// #include <engine/event/KeyDown.hpp>

// #include <engine/event/KeyUp.hpp>

// #include <engine/factory/ComponentFactory.hpp>

// #include <engine/event/Dispatcher.hpp>

// #include <engine/factory/EntityFactory.hpp>

// #include <engine/factory/Registry.hpp>

// #include <engine/factory/SystemFactory.hpp>

// #include <engine/meta/Hash.hpp>

// #include <engine/meta/Log.hpp>

// #include <engine/meta/Macro.hpp>

// #include <engine/meta/NoCopy.hpp>
/**
 * @file NoCopy.hpp
 * @brief Define NoCopy class
 */

/**
 * @brief A class to prohibit copying.
 *
 * The class which inherits from it will have no constructor per copy and no
 * equal operator. We prefer to pass an object by reference, which avoids the
 * duplication of data members of the class.
 */
struct NoCopy {
  NoCopy() = default;

  // copy assignment operator
  NoCopy& operator=(const NoCopy& rhs) = delete;

  // copy constructor
  NoCopy(const NoCopy& rhs) = delete;

 protected:
  ~NoCopy() = default;
};
// #include <engine/meta/NoMove.hpp>
/**
 * @file NoMove.hpp
 * @brief Define NoMove class
 */

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
// #include <engine/meta/RTTI.hpp>

// #include <engine/meta/Random.hpp>

#include <random>

/**
 * @brief Generate a random integer
 *
 * @param min Minimum number inclusive
 * @param max Maximum number inclusive
 * @return float Returns number between min-max, inclusive
 */
inline float random(const float min, const float max) {
  // this  function assumes max > min, you may want
  // more robust error checking for a non-debug build
  assert(max > min);
  float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

  // generate (in your case) a float between 0 and (4.5-.78)
  // then add .78, giving you a float between .78 and 4.5
  float range = max - min;
  return (random * range) + min;
}
// #include <engine/meta/Singleton.hpp>

// #include <engine/pool/ComponentArray.hpp>

// #include <engine/pool/IPool.hpp>

// #include <engine/pool/Pool.hpp>

// #include <engine/system/LogicalSystem.hpp>

// #include <engine/system/PhysicalSystem.hpp>

// #include <engine/system/RendererSystem.hpp>
