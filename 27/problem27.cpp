#include <iostream>
bool is_prime(int n) {
	if (n < 2) {
		return false;
	}

	for (int x = 2; x <= (int)n/2; x++){
		if (n % x == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	int n = 0;
	int result = 0;
	int a = -999;
	int b = -999;
	bool was_prime;
	int max_num_primes = 0;
	int ans;
	while (a < 1000) {
		b = 0;
		while (b < 1000) {
			int num_primes = 0;
			n = 0;
			do {
				result = n*n + a*n + b;
				if ((was_prime = is_prime(result))) {
					num_primes++;
				}
				n++;
			} while(was_prime);

			if (num_primes > max_num_primes){
				std::cout << "(" << a << "," << b << ") -- " << num_primes << std::endl;
				max_num_primes = num_primes;
				ans = a*b;
			}

			b++;
		}
		a++;
	}

	std::cout << "answer: " << ans;
	return 0;
}
