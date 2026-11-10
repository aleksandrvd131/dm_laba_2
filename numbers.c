#include "numbers.h"
#include "binpow.h"
#include "Euclid.h"
#include <stdint.h>
#include <math.h>

// Подсчёт количества всех натуральных делителей d(n)
uint64_t divisors_cnt(uint64_t n) {
    uint64_t result = 0;
    for (uint64_t i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result += 1;
            if (i * i != n) {
                result += 1;
            }
        }
    }
    return result;
}

// Подсчёт суммы всех натуральных делителей sigma(n)
uint64_t divisors_sum(uint64_t n) {
    uint64_t result = 0;
    for (uint64_t i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            result += i;
            if (i * i != n) {
                result += (n / i);
            }
        }
    }
    return result;
}

// Подсчёт количества различных простых делителей omega(n)
uint64_t prime_divisors_cnt(uint64_t n) {
    uint64_t result = 0;
    for (uint64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            result += 1;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        result += 1;
    }
    return result;
}

// Функция Эйлера phi(n) - количество чисел от 1 до n, взаимно простых с n
uint64_t Euler(uint64_t n) {
    uint64_t result = 0;
    for (uint64_t i = 1; i <= n; ++i) {
        if (gcd(n, i) == 1) {
            result += 1;
        }
    }
    return result;
}

// Функция Мёбиуса mu(n)
// Возвращает 0, если число делится на квадрат простого;
// иначе (-1)^k, где k - число простых сомножителей.
int8_t Moebius(uint64_t n) {
    uint64_t count = 0;
    for (uint64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            n /= i;
            count += 1;
            if (n % i == 0) {
                return 0; // делится на i^2
            }
        }
    }
    if (n > 1) {
        count += 1;
    }
    return (count % 2 == 1) ? -1 : 1;
}

// Функция Кармайкла lambda(n) - наименьшее m >= 1, такое что a^m = 1 (mod n)
// для всех a, взаимно простых с n
uint64_t Carmichael(uint64_t n) {
    for (uint64_t m = 1; m <= n; ++m) {
        int ok = 1;
        for (uint64_t a = 2; a <= n; ++a) {
            if (gcd(a, n) == 1 && binpow(a, m, n) != 1) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            return m;
        }
    }
    return n;
}

// Функция Мангольдта Lambda(n) = ln(p), если n = p^k (p - простое, k >= 1), иначе 0
double Mangoldt(uint64_t n) {
    if (n < 2) {
        return 0.0;
    }

    uint64_t base = 0;
    for (uint64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            base = i;
            while (n % i == 0) {
                n /= i;
            }
            break;
        }
    }

    // Если делителей в цикле не нашлось, то само n - простое число
    if (base == 0) {
        return log((double)n);
    }

    // Если после деления на все степени base осталось n > 1, то у числа больше одного простого делителя
    if (n > 1) {
        return 0.0;
    }

    return log((double)base);
}
