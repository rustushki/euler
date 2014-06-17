#include <gmp.h>

void fibonacci(int n, mpz_t* op1, mpz_t* op2) {
	if (n == 1) {
		mpz_set_ui(*op1, 0);
		mpz_set_ui(*op2, 1);
	} else if (n == 2) {
		mpz_set_ui(*op1, 1);
		mpz_set_ui(*op2, 2);
		fibonacci(n-1, op1, op2);
	} else if (n > 2) {
		mpz_t temp;
		mpz_init(temp);
		mpz_set(temp, *op2);
		mpz_add(*op2, *op1, temp);
		mpz_set(*op1, temp);
	}

}

int main() {
	mpz_t op1;
	mpz_t op2;
	mpz_init(op1);
	mpz_init(op2);
	mpz_set_ui(op1, 0);
	mpz_set_ui(op2, 0);

	for (int n = 1; n < 4784; n++) {
		fibonacci(n, &op1, &op2);
		gmp_printf("%Zd\n", op2);
	}

	return 0;
}
