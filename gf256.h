#pragma once
#include <stdint.h>

#define FIELD_SIZE 256

// Элемент поля GF(256) - многочлен степени < 8
typedef uint8_t gf256_pnom;

// Модуль - неприводимый многочлен степени 8
typedef uint16_t gf256_modulo;

// Определение номера старшего значащего бита (1-based)
uint8_t get_oldest_bit_index(uint16_t a);

// Вывод многочлена в читаемом математическом виде (например, x^8 + x^4 + x^3 + x^1 + 1)
void gf256_write_polynomial(uint16_t a);

// Ввод многочлена со стандартного потока (степени слагаемых через пробел до конца строки)
void gf256_read_polynomial(gf256_pnom *a);

// Взятие остатка от деления многочлена a на многочлен-модуль b в поле GF(2)
gf256_pnom gf256_mod(uint16_t a, gf256_modulo b);

// Проверка многочлена на неприводимость над GF(2)
int gf256_is_modulo(gf256_modulo a);

// Поиск и вывод всех неприводимых многочленов 8-й степени для GF(256)
void gf256_find_modules(void);

// Сложение двух элементов поля (побитовое XOR)
gf256_pnom gf256_add(gf256_pnom a, gf256_pnom b);

// Умножение двух элементов поля по модулю mod
gf256_pnom gf256_mul(gf256_pnom a, gf256_pnom b, gf256_modulo mod);

// Быстрое возведение многочлена a в степень n по модулю mod
gf256_pnom gf256_pow(gf256_pnom a, uint32_t n, gf256_modulo mod);

// Нахождение мультипликативного обратного элемента через малую теорему Ферма (a^(254) mod mod)
gf256_pnom gf256_inv(gf256_pnom a, gf256_modulo mod);
