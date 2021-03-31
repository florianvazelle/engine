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