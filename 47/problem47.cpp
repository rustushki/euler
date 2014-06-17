#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

#define SERIESLENGTH 4
#define PRIMEFACTORCOUNT 4
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
bool isPrime(long long n) {
	
	// 2 is prime; special case.
	if (n == 2) {
		return true;
	}

	// Generic control var.
	int x = 0;

	// Speed trick: cmath's sqrt is quite fast, but storing the result makes a
	// huge speed differents.
	double sqrtN = sqrt(n);

	// Iterate over all the collected primes thus far and check if they're
	// divisors.
	int p = 0;
	for (x = 0; p <= sqrtN; x++) {
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

bool has4DistinctPrimeFactors(long n) {
	std::vector<int> primeFactors;

	// Iterate over prime numbers.
	int p = 0;
	for (int x = 0; x < primes.size() && n >= 1; x++) {
		p = primes[x];

		// If the prime is a divisor of N,
		if (n % p == 0) {
			
			// Check if the prime number has already been marked as a divisor.
			bool found = false;
			for (int r = 0; r < primeFactors.size(); r++) {
				if (primeFactors[r] == p) {
					found = true;
					break;
				}
			}

			// If the prime number has already been marked as a divisor, don't
			// add it again.
			if (!found) {
				primeFactors.push_back(p);
			}

			// If the number of prime factors exceeds the number we're looking
			// for (4 according to problem 47), return false.
			if (primeFactors.size() > PRIMEFACTORCOUNT) {
				return false;
			}

			// Divide N by the prime factor.  
			n /= p;

			// Restart the loop from the beginning.
			// We technically need to check all prime numbers again, though
			// this function seems to work correctly for PRIMEFACTORCOUNT = 4,
			// even when we don't.
			x = -1;
		}

	}

	// Return true only if the size of the unique prime factor vector is equal
	// to the necessary count (i.e. 4).
	return (primeFactors.size() == PRIMEFACTORCOUNT);
}

int main() {

	// Let the clock begin.
	std::clock_t begin = std::clock();

	// Test runs show all primes under 700 should work.
	generatePrimes(700);

	int seriesCount = 0;
	for (long n = 2; n < 10000000; n++) {

		// Look for a series of SERIESLENGTH consequtive numbers numbers with
		// PRIMEFACTORCOUNT unique prime factors.
		if (has4DistinctPrimeFactors(n)) {
			seriesCount++;
		} else {
			seriesCount = 0;
		}

		// Output the result and break when found.
		if (seriesCount == SERIESLENGTH) {
			std::cout << "Found in: " << ((std::clock() - begin) / (double)CLOCKS_PER_SEC) << "s" << std::endl;
			std::cout << n - SERIESLENGTH + 1 << std::endl;
			break;
		}
	}

	return 0;
}
