#pragma once
#include <stdint.h>

// Быстрое бинарное возведение n в степень k (по модулю mod, если mod != 0)
uint64_t binpow(uint64_t n, uint64_t k, uint64_t mod);
