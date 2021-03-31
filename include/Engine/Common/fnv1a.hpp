#pragma once

#include <cstdint>

// Version "alternative" de l'algorithme FNV1 dit FNV1-a
// voir http://www.isthe.com/chongo/tech/comp/fnv/

#define FNV1_32_INIT ((uint32_t)0x811c9dc5)

uint32_t fnv_32a_str(const char *str);