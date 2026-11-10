#include "binpow.h"

// Бинарное возведение в степень O(log k)
uint64_t binpow(uint64_t n, uint64_t k, uint64_t mod) {
    uint64_t res = 1;
    while (k > 0) {
        if (k & 1) {
            res *= n;
            if (mod != 0) {
                res %= mod;
            }
        }
        n *= n;
        if (mod != 0) {
            n %= mod;
        }
        k >>= 1;
    }
    if (mod != 0) {
        return res % mod;
    }
    return res;
}
