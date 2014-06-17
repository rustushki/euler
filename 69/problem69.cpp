#include <iostream>

/* Problem 69 -
 *
 * Worked it out with programmatic experimentation and paper and pencil.
 *
 * Reasoning:
 *
 * 1. a and b are co primes if they have no common factors.
 *
 * 2. phi(n) = the number of co primes less than n.
 *
 * 3. n/phi(n) is minimized when n is prime.
 *
 * 4. If n has a prime factor p, all multiples of p less than n are not coprime.
 *
 * By 3 and 4, it stands to reason that a number which is the product of the
 * first r primes; where the product is less than 1,000,000; must be the
 * answer.
 *
 * 510,510.
 * qed.
 */

int main() {
	std::cout << 2*3*5*7*11*13*17 << std::endl;
	return 0;
}

