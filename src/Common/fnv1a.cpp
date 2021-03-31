#include <Engine/Common/fnv1a.hpp>

uint32_t fnv_32a_str(const char *str) {
  uint32_t hval    = FNV1_32_INIT;
  unsigned char *s = (unsigned char *)str; /* FNV-1a hash each octet in the buffer */
  while (*s) {
    /* xor the bottom with the current octet */
    hval ^= (uint32_t)*s++;
    /* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
    hval *= FNV_32_PRIME;
#else
    hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
#endif
  }

  /* return our new hash value */
  return hval;
}

uint64_t simple_hash(uint32_t x, uint32_t y) {
  const uint64_t a = static_cast<uint64_t>(x);
  const uint64_t b = static_cast<uint64_t>(y);

  const uint64_t h0 = (b << 32) | a;
  const uint64_t h1 = (a << 32) | b;

  return (x < y) ? h0 : h1;  // conditional move (CMOV) instruction
}