#include <Engine/Component/Transform.hpp>

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

RTTI_DEFINITION(Transform, IComponent)

// 2x2 row major Matrix multiply A*B
__m128 Mat2Mul(__m128 vec1, __m128 vec2) {
  return _mm_add_ps(_mm_mul_ps(vec1, VecSwizzle(vec2, 0, 3, 0, 3)),
                    _mm_mul_ps(VecSwizzle(vec1, 1, 0, 3, 2), VecSwizzle(vec2, 2, 1, 2, 1)));
}
// 2x2 row major Matrix adjugate multiply (A#)*B
__m128 Mat2AdjMul(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(_mm_mul_ps(VecSwizzle(vec1, 3, 3, 0, 0), vec2),
                    _mm_mul_ps(VecSwizzle(vec1, 1, 1, 2, 2), VecSwizzle(vec2, 2, 3, 0, 1)));
}
// 2x2 row major Matrix multiply adjugate A*(B#)
__m128 Mat2MulAdj(__m128 vec1, __m128 vec2) {
  return _mm_sub_ps(_mm_mul_ps(vec1, VecSwizzle(vec2, 3, 0, 3, 0)),
                    _mm_mul_ps(VecSwizzle(vec1, 1, 0, 3, 2), VecSwizzle(vec2, 2, 1, 2, 1)));
}

Transform Transform::inverse() const {
  const __m128 BCx = _mm_setr_ps(a.x, a.y, a.z, a.w);
  const __m128 BCy = _mm_setr_ps(b.x, b.y, b.z, b.w);
  const __m128 BCz = _mm_setr_ps(c.x, c.y, c.z, c.w);
  const __m128 BCw = _mm_setr_ps(d.x, d.y, d.z, d.w);

  // use block matrix method
  // A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code) means adjugate of A, |A|
  // (or detA in code) is determinant, tr(A) is trace

  // sub matrices
  __m128 A = VecShuffle_0101(BCx, BCy);
  __m128 B = VecShuffle_2323(BCx, BCy);
  __m128 C = VecShuffle_0101(BCz, BCw);
  __m128 D = VecShuffle_2323(BCz, BCw);

#if 0
	__m128 detA = _mm_set1_ps(inM.m[0][0] * inM.m[1][1] - inM.m[0][1] * inM.m[1][0]);
	__m128 detB = _mm_set1_ps(inM.m[0][2] * inM.m[1][3] - inM.m[0][3] * inM.m[1][2]);
	__m128 detC = _mm_set1_ps(inM.m[2][0] * inM.m[3][1] - inM.m[2][1] * inM.m[3][0]);
	__m128 detD = _mm_set1_ps(inM.m[2][2] * inM.m[3][3] - inM.m[2][3] * inM.m[3][2]);
#else
  // determinant as (|A| |B| |C| |D|)
  __m128 detSub =
      _mm_sub_ps(_mm_mul_ps(VecShuffle(BCx, BCz, 0, 2, 0, 2), VecShuffle(BCy, BCw, 1, 3, 1, 3)),
                 _mm_mul_ps(VecShuffle(BCx, BCz, 1, 3, 1, 3), VecShuffle(BCy, BCw, 0, 2, 0, 2)));
  __m128 detA = VecSwizzle1(detSub, 0);
  __m128 detB = VecSwizzle1(detSub, 1);
  __m128 detC = VecSwizzle1(detSub, 2);
  __m128 detD = VecSwizzle1(detSub, 3);
#endif

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

  // apply adjugate and store, here we combine adjugate shuffle and store shuffle
  _mm_store_ps(&r[0][0], VecShuffle(X_, Y_, 3, 1, 3, 1));
  _mm_store_ps(&r[1][0], VecShuffle(X_, Y_, 2, 0, 2, 0));
  _mm_store_ps(&r[2][0], VecShuffle(Z_, W_, 3, 1, 3, 1));
  _mm_store_ps(&r[3][0], VecShuffle(Z_, W_, 2, 0, 2, 0));

  return r;
}