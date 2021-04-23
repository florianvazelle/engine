#pragma once

#include <immintrin.h>

#include <Engine/Component/IComponent.hpp>
#include <cmath>

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

  float operator*(const float4& vec) const { return (x * vec.x + y * vec.y + z * vec.z); }

  float4 operator+(const float4& vec) const { return {x + vec.x, y + vec.y, z + vec.z, 1}; }
  float4 operator-(const float4& vec) const { return {x - vec.x, y - vec.y, z - vec.z, 1}; }
  float4 operator-() const { return {-x, -y, -z, 1}; }

  friend std::ostream& operator<<(std::ostream& os, const float4& f) {
    os << "(" << f.x << ", " << f.y << ", " << f.z << ", " << f.w << ")";
    return os;
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
  Transform inverse() const;

  float4 globalToLocal(const float4& vec) const { return inverse() * vec; }
  float4 localToGlobal(const float4& vec) const { return (*this) * vec; }

  /**
   * @brief Intersection of two cube
   *
   * In local space, we check, for each edges of a cube, if it's intersect a face of the other cube.
   * For this, we compute a segment - plane intersection and we check if the face contains the
   * impact point
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
             (-1 <= ps1.x && ps1.x <= 1 && -1 <= ps1.y && ps1.y <= 1 && -1 <= ps1.x && ps1.x <= 1);
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
  };
};