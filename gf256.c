#include "gf256.h"
#include <stdio.h>

// Номер старшего бита (1-based: для a=1 возвращает 1, для a=0 возвращает 0)
uint8_t get_oldest_bit_index(uint16_t a) {
    uint8_t result = 0;
    while (a > 0) {
        ++result;
        a >>= 1;
    }
    return result;
}

// Печать многочлена в виде x^k + ... + 1
void gf256_write_polynomial(uint16_t a) {
    if (a == 0 || a == 1) {
        printf("%d", a);
        return;
    }

    uint8_t idx = get_oldest_bit_index(a) - 1;
    printf("x^%d", idx);
    --idx;

    while (idx >= 1) {
        if ((a >> idx) & 1) {
            printf(" + x^%d", idx);
        }
        --idx;
    }

    if (a & 1) {
        printf(" + 1");
    }
}

// Считывание многочлена: список степеней x через пробел до конца строки
void gf256_read_polynomial(gf256_pnom *a) {
    uint32_t x;
    char tmp;
    *a = 0;
    while (scanf("%u%c", &x, &tmp) == 2) {
        *a = (gf256_pnom)(*a | (1 << x));
        if (tmp == '\n') {
            break;
        }
    }
}

// Деление с остатком в кольце многочленов над GF(2)
gf256_pnom gf256_mod(uint16_t a, gf256_modulo mod) {
    uint8_t mod_oldest_bit_index = get_oldest_bit_index(mod);
    uint8_t idx;
    while ((idx = get_oldest_bit_index(a)) >= mod_oldest_bit_index) {
        a ^= (uint16_t)(mod << (idx - mod_oldest_bit_index));
    }
    return (gf256_pnom)a;
}

// Проверка неприводимости многочлена (нет делителей степени от 1 до 7)
int gf256_is_modulo(gf256_modulo a) {
    for (gf256_modulo i = 2; i < FIELD_SIZE; ++i) {
        if (!gf256_mod(a, i)) {
            return 0;
        }
    }
    return 1;
}

// Поиск всех неприводимых многочленов 8-й степени над GF(2)
void gf256_find_modules(void) {
    uint32_t cnt = 0;
    for (gf256_modulo i = FIELD_SIZE + 1; i < (FIELD_SIZE << 1); i += 2) {
        if (gf256_is_modulo(i)) {
            printf("%u. ", cnt + 1);
            gf256_write_polynomial(i);
            printf("\n");
            ++cnt;
        }
    }
}

// Сложение в GF(256)
gf256_pnom gf256_add(gf256_pnom a, gf256_pnom b) {
    return (gf256_pnom)(a ^ b);
}

// Умножение в GF(256) по модулю mod
gf256_pnom gf256_mul(gf256_pnom a, gf256_pnom b, gf256_modulo mod) {
    uint16_t result = 0;
    uint32_t i = 0;
    while (b > 0) {
        if (b & 1) {
            result ^= (uint16_t)(a << i);
        }
        b >>= 1;
        ++i;
    }
    return gf256_mod(result, mod);
}

// Быстрое бинарное возведение в степень в GF(256)
gf256_pnom gf256_pow(gf256_pnom a, uint32_t n, gf256_modulo mod) {
    gf256_pnom result = 1;
    while (n > 0) {
        if (n & 1) {
            result = gf256_mul(result, a, mod);
        }
        a = gf256_mul(a, a, mod);
        n >>= 1;
    }
    return result;
}

// Мультипликативное обращение в GF(256) через малую теорему Ферма
gf256_pnom gf256_inv(gf256_pnom a, gf256_modulo mod) {
    return gf256_pow(a, FIELD_SIZE - 2, mod);
}
