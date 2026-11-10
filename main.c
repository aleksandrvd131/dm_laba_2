#include <stdio.h>
#include <inttypes.h>
#include "gf256.h"
#include "Euclid.h"
#include "binpow.h"
#include "numbers.h"

int main(void) {
    int problem = 0;
    printf("Choose problem (13, 14 or 15): ");
    if (scanf("%d", &problem) != 1) {
        return 1;
    }

    switch (problem) {
        case 13: {
            // Поиск и вывод всех неприводимых многочленов степени 8 над GF(2)
            gf256_find_modules();

            gf256_pnom a = 0, b = 0;
            printf("\nInput two GF256 polynomials:\n");
            gf256_read_polynomial(&a);
            gf256_read_polynomial(&b);

            printf("Sum: ");
            gf256_write_polynomial(gf256_add(a, b));

            printf("\nMultiplication by modulo 283: ");
            gf256_write_polynomial(gf256_mul(a, b, 283));

            printf("\nInversion to A by modulo 283: ");
            gf256_write_polynomial(gf256_inv(a, 283));

            printf("\nInversion to B by modulo 283: ");
            gf256_write_polynomial(gf256_inv(b, 283));
            printf("\n");
            break;
        }

        case 14: {
            uint64_t a = 0, b = 0;
            int64_t x = 0, y = 0;

            printf("Input two positive integers: ");
            if (scanf("%" PRIu64 " %" PRIu64, &a, &b) != 2) {
                return 1;
            }

            printf("GCD of A and B: %" PRIu64 "\n", gcd(a, b));

            extended_gcd(a, b, &x, &y, 0);
            printf("Bezout's identity for A and B: %" PRIu64 " = %" PRIi64 " * A + %" PRIi64 " * B\n", gcd(a, b), x, y);

            printf("A ^ B = %" PRIu64 "\n", binpow(a, b, 0));

            extended_gcd(a, 67, &x, &y, 67);
            printf("A^(-1) mod 67 by Euclid's algorithm: %" PRIi64 "\n", x % 67);
            printf("A^(-1) mod 67 by Binary Power algorithm: %" PRIu64 "\n", binpow(a, 67 - 2, 67));
            break;
        }

        case 15: {
            uint64_t n = 0;
            printf("Input one positive integer: ");
            if (scanf("%" PRIu64, &n) != 1) {
                return 1;
            }

            printf("Moebius function: %d\n", Moebius(n));
            printf("Divisors amount function: %" PRIu64 "\n", divisors_cnt(n));
            printf("Euler function: %" PRIu64 "\n", Euler(n));
            printf("Divisors sum function: %" PRIu64 "\n", divisors_sum(n));
            printf("Prime divisors amount function: %" PRIu64 "\n", prime_divisors_cnt(n));
            printf("Carmichael function: %" PRIu64 "\n", Carmichael(n));
            printf("Mangoldt function: %lf\n", Mangoldt(n));
            break;
        }

        default:
            printf("Unknown problem: %d\n", problem);
            break;
    }

    return 0;
}
