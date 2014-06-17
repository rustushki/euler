#include <iostream>
#include <cmath>

bool isPrime(int n) {
	if (n == 2) {
		return true;
	}

	for (int x = 2; x*x <= n; x++) {
		if (n % x == 0) {
			return false;
		}
	}

	return (n >= 2);
}

bool isTruncatablePrime(int n) {

	// Single Digit Numbers Are Not Counted.
	if (n <= 10) {
		return false;
	}

	// Truncate the Right Digit off until nothing left.
	int r = n;
	while (r >= 1) {
		// Is the result still Prime?
		if (!isPrime(r)) {
			return false;
		}

		r /= 10;
	}

	// Truncate Left Digit off until Nothing Left.
	r = n;
	while (r != 0) {
		// Place of the HO digit
		short place = log10(r);

		// What to divide r by to get the value of the HO digit
		int denominator = pow(10, place);

		// HO digit.
		short hoDigit = r / denominator;

		// Truncate off the HO digit.
		r -= hoDigit * denominator;
		
		// Is the resulting number still Prime?
		if (r != 0 && !isPrime(r)) {
			return false;
		}
	}

	return true;
}

int main() {
	// Sum Result Here.
	int sum = 0;

	// Single Digits Don't Count.
	int x = 11;

	// According to Problem 37, there are only 11 Prime Number truncatable from
	// R->L and L->R.
	int primeCount = 0;
	while (primeCount < 11) {

		// If x is truncatable ...
		if (isTruncatablePrime(x)) {
			std::cout << x << std::endl;
			sum += x;
			primeCount++;
		}
		
		// Only check odds.
		x+=2;
	}

	std::cout << "Sum of the 11 Truncatable Primes: " << sum << std::endl;

	return 0;
}
