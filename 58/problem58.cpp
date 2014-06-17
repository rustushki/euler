#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

std::vector<int> primes;

/* isPrime - 3 phase prime number sieve.  Phase #1: If N is 2, N is prime.
 * Phase #2: divide N against the list of sorted, generated primes.  If the
 * current prime is greater than the square root of N, N is prime. Phase 3:  If N is not
 * divisible by all primes collected thus far less than the square root of N,
 * test all numbers from the greatest prime collected thus far to the square
 * root if N.  If no divisor can be found, N is prime.  If any divisor for N
 * may be found less than the square root of N during Phase #2 and #3, N is not
 * prime.
 */
bool isPrime(unsigned long long n) {
	
	// 2 is prime; special case.
	if (n == 2) {
		return true;
	}

	// Generic control var.
	unsigned long long x = 0;

	// Speed trick: cmath's sqrt is quite fast, but storing the result makes a
	// huge speed differents.
	long double sqrtN = sqrt(n);

	// Iterate over all the collected primes thus far and check if they're
	// divisors.
	unsigned long long p = 0;
	for (x = 0; p <= sqrtN && x < primes.size(); x++) {
		p = primes[x];
		if (n % p == 0) {
			return false;
		}

	}

	// If divisor not found so far, check all potential divisors less than the
	// sqrt of N.
	for (x = p+1; x <= sqrtN; x++) {
		if (n % x == 0) {
			return false;
		}
	}

	// If no divisor is found, N is prime.
	return true;
}

/* generatePrimes - genate a sorted, ascending list of primes less than the
 * provided integer.
 */
void generatePrimes(int max) {
	primes.clear();
	primes.push_back(2);

	// Only test odds
	for (int n = 3; n < max; n+=2) {
		if (isPrime(n)) {
			primes.push_back(n);
		}
	}
}

int main() {

	generatePrimes(112000);

	unsigned long long cornerCount = 1;
	unsigned long long primeCount  = 0;
	unsigned long long cornerNE    = 0;
	unsigned long long cornerNW    = 0;
	unsigned long long cornerSW    = 0;
	unsigned long long cornerSE    = 1;
	unsigned long long between     = 0;

	for (unsigned long long sideLength = 3; ; sideLength += 2) {

		cornerCount += 4;

		between = sideLength - 1;

		cornerNE = cornerSE + between;
		cornerNW = cornerNE + between;
		cornerSW = cornerNW + between;
		cornerSE = cornerSW + between;

		if (isPrime(cornerNE)) {
			primeCount++;
		}
		if (isPrime(cornerNW)) {
			primeCount++;
		}
		if (isPrime(cornerSW)) {
			primeCount++;
		}
		if (isPrime(cornerSE)) {
			primeCount++;
		}

		//std::cout << primeCount << "/" << cornerCount << std::endl;
		if ((double) primeCount/cornerCount < .1) {
			std::cout << sideLength << std::endl;
			break;
		}
	}

	return 0;
}
