#include <iostream>
#include <vector>
#include <cmath>

// Determine if a given number is prime.
bool isPrime(unsigned long long n) {
	if (n <= 2) {

		if (n == 2) {
			return true;

		// 0 and 1
		} else {
			return false;
		}
	}

	if (n % 2 == 0) {
		return false;
	}

	for (int x = 3; x <= sqrt(n); x+=2) {
		if (n % x == 0) {
			return false;
		}
	}

	return true;
}

int countDigits(int x) {
	int maxDigits = 0;
	int tempX = x;
	while (tempX >= 1) {
		tempX /= 10;
		maxDigits++;
	}

	return maxDigits;
}

std::vector<int> digitize(int x) {
	std::vector<int> digits;

	while (x >= 1) {
		int d = x % 10;
		digits.push_back(d);
		x /= 10;
	}

	return digits;
}

int numberize(std::vector<int> digits) {
	int num = 0;

	for (int x = 0; x < digits.size(); x++) {
		num += digits[x] * pow(10, x);
	}

	return num;
}

void swapPlacesWithDigit(std::vector<int>& digits, std::vector<int> v, int digit) {
	for (std::vector<int>::iterator x = v.begin(); x < v.end(); x++) {
		digits[(*x)] = digit;
	}
}

bool primeFamilyGte8(int x, std::vector<int> mask) {
	std::vector<int> digits = digitize(x);

	// These will store the results of each prime number test.  If fail > 2,
	// pass can't be == 8, but pass must be = 8 in order to pass this overall
	// test.  Consequently, fail > 2 is a much faster way to rule out a mask
	// than pass = 8.
	int fail = 0;
	int pass = 0;

	// Count the number of digits in the number.  This prevents the successful
	// application of a mask which would drop the total digit count.  For
	// example: 109 is technically 000109 which is technically a successful
	// mask of ***109.  The problem is that 109 is not 6 digits.
	int digitCount = countDigits(x);

	// Iterate over each digit to use on the mask.
	for (int d = 0; d <= 9; d++) {

		// Apply a digit mask to the provided number.
		swapPlacesWithDigit(digits, mask, d);
		int tryNum = numberize(digits);


		// PASS: If the digit masked number is prime and it's digit count
		// matches the digit count of the provided prime,
		if (isPrime(tryNum) && countDigits(tryNum) == digitCount) {
			pass++;
		} else {
			fail++;
		}

		// Overall test fails if prior check fails more than twice for provided
		// mask.
		if (fail > 2) {
			return false;
		}
	}

	// Overall test only succeeds if the mask successfully finds 8 primes.
	if (pass == 8) {

		// This is here for debugging.  Uncomment to see the matching number family.
		/*
		for (int d = 0; d <= 9; d++) {
			swapPlacesWithDigit(digits, mask, d);
			int tryNum = numberize(digits);
			if (isPrime(tryNum) && countDigits(tryNum) == digitCount) {
				std::cout << numberize(digits) << ", ";
			}
		}
		std::cout << std::endl;
		*/

		return true;
	}

	return false;
}

int main() {

	// Generate a list of primes in the expected/guess range.
	std::vector<int> primes;
	for (int x = 100000; x <= 499999; x++) {
		if (isPrime(x)) {
			primes.push_back(x);
		}
	}


	// Iterate over each prime.
	for (int y = 0; y < primes.size(); y++) {
		int x = primes[y];


		// Count the digits in the prime.
		int ct = countDigits(x);

		// Generate each possible 'digit mask' and execute 'primeFamilyGte8' on
		// that mask.  This portion could be improved by modifying it so that
		// it doesn't assume a six digit number.  The assumption manifests
		// itself in having 5 nested for loops.
		for (int a = 0; a < ct; a++) {
			std::vector<int> m;
			m.push_back(a);
			if (primeFamilyGte8(x, m)) {
				std::cout << x;
				return 0;
			}

			for (int b = a+1; b < ct; b++) {
				m.push_back(b);
				if (primeFamilyGte8(x, m)) {
					std::cout << x;
					return 0;
				}

				for (int c = b+1; c < ct; c++) {
					m.push_back(c);

					if (primeFamilyGte8(x, m)) {
						std::cout << x;
						return 0;
					}

					for (int d = c+1; d < ct; d++) {
						m.push_back(d);

						if (primeFamilyGte8(x, m)) {
							std::cout << x;
							return 0;
						}

						for (int e = d+1; e < ct; e++) {
							m.push_back(e);

							if (primeFamilyGte8(x, m)) {
								std::cout << x;
								return 0;
							}
							m.pop_back();
						}
						m.pop_back();
					}
					m.pop_back();
				}
				m.pop_back();
			}
			m.pop_back();
		}
	}

	return 0;
}
