#include "Euclid.h"

// Классический алгоритм Евклида для поиска НОД
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b > 0) {
        uint64_t tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Расширенный алгоритм Евклида
// Находит НОД(a, b) и коэффициенты Безу x, y такие, что a*x + b*y = gcd(a, b).
// Если modulo != 0, вычисляет результат по модулю modulo.
uint64_t extended_gcd(uint64_t a, uint64_t b, int64_t *x, int64_t *y, uint64_t modulo) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x_t = 0;
    int64_t y_t = 0;
    uint64_t gcd_t = extended_gcd(b % a, a, &x_t, &y_t, modulo);

    if (modulo != 0) {
        int64_t mul = (int64_t)(b / a);
        int64_t term = (x_t * mul) % (int64_t)modulo;
        *x = (y_t - term) % (int64_t)modulo;
        if (*x < 0) {
            *x += (int64_t)modulo;
        }
        *y = x_t % (int64_t)modulo;
        if (*y < 0) {
            *y += (int64_t)modulo;
        }
    } else {
        *x = y_t - x_t * (int64_t)(b / a);
        *y = x_t;
    }

    return gcd_t;
}
