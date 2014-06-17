#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <gmp.h>

/**
 * Euler #66
 *
 * This is the Chakravala Method implemented with the GMP library.  It
 * calculates the minimal X and a Y, such that X^2 - D * Y^2 = 1 for all D
 * between 1 and 1000.
 *
 * Then it outputs the D for the largest minimal D.
 */
int main() {

	// This will hold the D value for the largest minimal X.
	int answerD = 1;

	// This will hold the largest minimal X.
	mpz_t biggestX;
	mpz_init(biggestX);
	mpz_set_ui(biggestX, 0);

	// These are some helper variables which are used below.
	mpz_t moduloK;
	mpz_t newA;
	mpz_t newB;
	mpz_t newK;
	mpz_t a;
	mpz_t b;
	mpz_t k;
	mpz_init(moduloK);
	mpz_init(newA);
	mpz_init(newB);
	mpz_init(newK);
	mpz_init(a);
	mpz_init(b);
	mpz_init(k);
	// Execute Chakravala Method on each non-square root D.
	for (int D = 1; D < 1000; D++) {

		// If D is a square, go to the next D.
		if (sqrt(D) == (int) sqrt(D)) {
			continue;
		}
	
		// Choose x = a and y = b, such that a^2 - D * y^2 = a^2 - D = k.

		// Choose A to be 1 higher than the Sqrt of D.
		mpz_set_ui(a, 0);
		mpz_add_ui(a, a, sqrt(D) + 1);

		// Set B to 1
		mpz_set_ui(b, 0);
		mpz_add_ui(b, b, 1);

		// Set K = a^2 - D.
		mpz_pow_ui(k, a, 2);
		mpz_sub_ui(k, k, D);

		// While K != 1
		while (mpz_cmp_ui(k, 1) != 0) {

			// Find an m such that |m^2 - D| is minimal and a+bm % k == 0.
			long minMSquaredMinusD = -1;
			long m = 0;
			for (m = 1; ; m++) {

				// Condition #2
				// If (A + B*M) % K == 0,
				mpz_set_ui(moduloK, 0);
				mpz_mul_ui(moduloK, b, m);
				mpz_add(moduloK, moduloK, a);
				mpz_mod(moduloK, moduloK, k);
				if (mpz_cmp_ui(moduloK, 0) == 0) {

					// If a minimum has not yet been found, initialize it to
					// this value.
					long possibleMin = labs(m*m - D);
					if (minMSquaredMinusD != -1) {
						if (possibleMin < minMSquaredMinusD) {
							minMSquaredMinusD = possibleMin;
							break;
						}

					// If abs(M-M - D) is smaller than that of the smallest
					// value encountered so far... 
					} else {
						minMSquaredMinusD = possibleMin;
						break;
					}
				}
			}

			// Initialize newA, newB, and newK
			mpz_set_ui(newA, 0);
			mpz_set_ui(newB, 0);
			mpz_set_ui(newK, 0);

			// Recompute A.  newA = (a * m + D * b) / labs(k);
			mpz_mul_ui(newA, a, m);
			mpz_mul_ui(newB, b, D);
			mpz_add(newA, newA, newB);
			mpz_abs(newK, k);
			mpz_cdiv_q(newA, newA, newK);


			// Recompute B.  newB = (a + b * m) / labs(k);
			mpz_set_ui(newB, 0);
			mpz_mul_ui(newB, b, m);
			mpz_add(newB, newB, a);
			mpz_cdiv_q(newB, newB, newK);


			// Recompute K. newK = (m*m - D) / k;
			mpz_set_ui(newK, 0);
			mpz_set_si(newK, m*m - D);
			mpz_cdiv_q(newK, newK, k);

			mpz_set(a, newA);
			mpz_set(b, newB);
			mpz_set(k, newK);

			if (mpz_cmp(a, biggestX) > 0) {
				mpz_set(biggestX, a);
				answerD = D;
			}
		}

		/*
		std::cout << "D = " << D << "; ";
		gmp_printf("a = %Zd; ", a);
		gmp_printf("b = %Zd; ", b);
		gmp_printf("k = %Zd; ", k);
		std::cout << "\n";
		*/
	}

	std::cout << "Answer: " << std::endl;
	std::cout << "D = " << answerD << "; ";
	gmp_printf("x = %Zd; ", biggestX);

	return 0;
}
