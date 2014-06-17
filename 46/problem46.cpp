#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

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

int main() {
	// Let the clock begin.
	std::clock_t begin = std::clock();

	// Cache all the primes below 6000; arbitrarily chosen limit.
	generatePrimes(60000);

	// Search for an X where X is composite and there exists no Z and no Prime
	// Number P where P+2*Z^2 == X; thus breaking Christian Goldbach's
	// proposal.
	int x;
	for (x = 9; ; x += 2) {

		// Move On if X is prime.
		if (isPrime(x)) {
			continue;
		}

		// Found = true indicates that there exists a Z and P which satisfies
		// the conditions.  We want to fail to find a Z and P.
		//
		// Iterate over our cache of primes, 
		bool found = false;
		for (int y = 0; y < primes.size(); y++) {

			// Store the P
			int p = primes[y];
			int diff = x-p;

			// diff == 0 shouldn't happen; else X is prime.  X shouldn't be
			// prime since we checked for that above.
			if (diff <= 0) {
				break;
			}

			// Search for Z.
			double z = sqrt(diff / 2);

			// Z is valid only when Z is an integer.
			found = (z == (int)z);

			// Found Z and P, X is not the number we're looking for.
			if (found) {
				break;
			}
		}

		// Z and P could not be found, break out of here.
		if (!found) {
			break;
		}
	}


	std::cout << "Found in: " << ((std::clock() - begin) / (double)CLOCKS_PER_SEC) << "s" << std::endl;
	std::cout << x << std::endl;

	return 0;
}
