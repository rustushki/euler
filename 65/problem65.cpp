#include <iostream>
#include <gmp.h>
#include <cstring>


int main() {

	// I feel bad because in this problem I got lazy and used GMP.  I didn't
	// feel like writing a carry adder and a carry multiplier.

	// Iterate over each convergent.
	bool lastConvergent = true;
	mpz_t lastN;
	mpz_t lastD;
	mpz_init_set_ui(lastN, 0);
	mpz_init_set_ui(lastD, 1);
	for (int x = 99; x > 0; x--) {
		int d = 1;

		// Every 3rd convergent's denominator should be 2*k
		if ((x + 1) % 3 == 0) {
			int k = (x+1)/3;
			d = 2*k;
		}

		if (lastConvergent) {
			mpz_set_ui(lastN, 1);
			mpz_set_ui(lastD, d);
			lastConvergent = false;
		} else {

			// N`/D` = nD + (N/D)
			mpz_t tempN;
			mpz_init(tempN);
			mpz_mul_ui(tempN, lastD, d);
			mpz_add(lastN, lastN, tempN);


			// Swap N` and D` (i.e., 1 / (N`/D`)
			mpz_swap(lastD, lastN);
		}
	}

	// Add 2 to the number
	mpz_t tempD;
	mpz_init(tempD);
	mpz_mul_ui(tempD, lastD, 2);
	mpz_add(lastN, lastN, tempD);

	char* str = mpz_get_str(NULL, 10, lastN);
	int digitSum = 0;
	for (int x = 0; x < strlen(str); x++) {
		digitSum += str[x] - 0x30;
	}

	std::cout << digitSum << std::endl;

	return 0;
}
