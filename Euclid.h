#pragma once
#include <stdint.h>

// Наибольший общий делитель (НОД) двух чисел
uint64_t gcd(uint64_t a, uint64_t b);

// Расширенный алгоритм Евклида: нахождение НОД и коэффициентов Безу (a*x + b*y = gcd)
uint64_t extended_gcd(uint64_t a, uint64_t b, int64_t *x, int64_t *y, uint64_t modulo);
