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

	// Generate all primes below 4000.  I don't exactly understand why 4000.
	// It can be a little less that 4000, but no less than ~3900.  The program
	// runs quite efficiently if this number is as high as 40,000.
	//
	// Speculation:  Suppose you have 10 sequential primes each about ~100,000,
	// but all less than 100,000.  The sum of these 10 primes is equal to 1M.
	// In this case, the series length is only 10 consecutive primes--which is
	// pretty short.  T/f, the maximum prime up for consideration should be
	// significantly less that 100K.
	//
	// Further, if such a prime existed (one which may be the sum of 10
	// consecutive primes, all about 100K each): it's worth pointing out that
	// 953 is the prime beneath 1000 which is the sum of the most consecutive
	// primes.  It's series length is 21, only 10 * 2.  Surely there exists a
	// series larger than 10 for our 1000000 case.
	generatePrimes(4000);

	// Count the total number of primes in our generated list.
	int primeCount = primes.size();

	// Init the maximum series length.
	int maxSeriesLength = 0;

	// Init the Answer.  2 is prime, so this seems like good initter.
	int ans = 2;


	// The starting index of the series of primes will be 0.  Increment the
	// starting index up to the maximum number of primes.
	for (int start = 0; start < primeCount; start++) {

		// The ending index will be the maximum number of primes, decrement it
		// until it equals the starting index.
		for (int end = primeCount - 1; end > start; end--) {

			// The Trick:
			// If the series length (end - start) is less than the
			// maxSeriesLength thus far, don't bother continuing to evaluate
			// this series.  Huge time savings here since we started with the
			// maximum series length first.
			if (end - start < maxSeriesLength) {
				break;
			}

			// Iterate over the series from end to start.  Build a sum.  Quit if the
			// sum is greater than 1,000,000.
			long long seriesSum = 0;
			for (int idx = end; idx >= start; idx--) {
				seriesSum += primes[idx];

				if (seriesSum > 1000000) {
					break;
				}
			}

			// Three conditions are required for a sum to replace the max sum thus far:
			// 1. It must be less than 1000000
			// 2. The series of primes that created it must be bigger than the last number's series.
			// 3. It must be a prime.
			// AND evaluation in this sequence is most efficient.
			if (seriesSum < 1000000 && (end - start > maxSeriesLength) && isPrime(seriesSum)) {
				ans = seriesSum;
				maxSeriesLength = end - start;
			}
		}
	}

	std::cout << "Found in: " << ((std::clock() - begin) / (double)CLOCKS_PER_SEC) << "s" << std::endl;

	std::cout << "Answer: " << ans << ";  Length: " << maxSeriesLength << std::endl;


	return 0;
}
