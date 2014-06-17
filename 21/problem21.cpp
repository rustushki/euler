#include <iostream>

#define UNDER 100000

int sumDivisors(int n) {

	int sum = 0;
	for(int x = 1; x <= n/2; x++) {
		if (n % x == 0) {
			sum += x;
		}
	}
	return sum;
}

int main() {

	int divSum[UNDER];

	bool isAmicableNumber[UNDER];

	for (int n = 0; n < UNDER; n++) {
		isAmicableNumber[n] = false;
		divSum[n] = sumDivisors(n);
	}

	for (int a = 0; a < UNDER; a++) {
		for (int b = 0; b < UNDER; b++) {
			if (a != b) {
				if (a == divSum[b] && b == divSum[a]) {
					isAmicableNumber[b] = true;
					isAmicableNumber[a] = true;
				}
			}
		}
	}

	int sum = 0;
	for (int n = 0; n < UNDER; n++) {
		if (isAmicableNumber[n]) {
			sum += n;
		}
	}

	std::cout << sum << std::endl;


	return 0;
}
