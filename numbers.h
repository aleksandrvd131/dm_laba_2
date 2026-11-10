#pragma once
#include <stdint.h>
#include <math.h>

// Количество делителей d(n)
uint64_t divisors_cnt(uint64_t n);

// Сумма делителей sigma(n)
uint64_t divisors_sum(uint64_t n);

// Количество различных простых делителей omega(n)
uint64_t prime_divisors_cnt(uint64_t n);

// Функция Эйлера phi(n)
uint64_t Euler(uint64_t n);

// Функция Мёбиуса mu(n)
int8_t Moebius(uint64_t n);

// Функция Кармайкла lambda(n)
uint64_t Carmichael(uint64_t n);

// Функция Мангольдта Lambda(n)
double Mangoldt(uint64_t n);
