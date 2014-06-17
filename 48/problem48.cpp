#include <gmp.h>

int main() {
	mpz_t ans;
	mpz_t temp;

	mpz_init(ans);
	mpz_init(temp);

	for (int i = 1; i <= 1000; i++){
		mpz_set_ui(temp, i);
		mpz_pow_ui(temp, temp, i);
		mpz_add(ans, ans, temp);
	}

	gmp_printf("%Zd\n", ans);
	return 0;
}
