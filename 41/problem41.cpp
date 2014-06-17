#include <iostream>
#include <vector>
#include <cmath>

// Determine if a given number is prime.
bool isPrime(unsigned long long n) {
	if (n == 2) {
		return true;
	}

	for (int x = 2; x <= sqrt(n); x++) {
		if (n % x == 0) {
			return false;
		}
	}

	return true;
}

// Convert a digital vector into an integer.
std::vector<short> longToDigitVec(unsigned long long i) {

	std::vector<short> digitVec;
	while (i >= 1) {
		digitVec.push_back(i % 10);
		i /= 10;
	}

	return digitVec;

}

// Convert an integer into a digital vector.
unsigned long long digitVecToInt(std::vector<short> digitVec) {
	unsigned long long sum = 0;
	for (int x = 0; x < digitVec.size(); x++) {
		sum += digitVec[x]*pow(10, x);
	}
	return sum;
}

// Swap positions p and q in vector n.
std::vector<short> swap(std::vector<short> n, int p, int q) {
	short t = n[q];
	n[q] = n[p];
	n[p] = t;
	return n;
}

// Given a pandigital number, find the next smallest one.  Returns the number
// provided if there is not one smaller.
unsigned long long next(unsigned long long panDigital) {

	// q and p are indexes into a vector of digits.
	int q = 0;
	int p = 0;

	// set to true when the next smallest number is found.
	bool found = false;

	// Convert our pandigital number into a vector of digits.
	std::vector<short> n = longToDigitVec(panDigital);

	// Increment q from 0 to the size of the vector.
	while (q < n.size()) {

		// When q is larger than p
		while (p < q) {

			// If the pandigital produced by swapping p and q is less than the
			// current pandigital,
			if (digitVecToInt(swap(n, p, q)) < digitVecToInt(n)) {

				// The current will pandigital will now be the result of
				// swapping the two numbers.
				n = swap(n, p, q);

				// we know that the digit at q is now the next largest number
				// for its place..  t/f decrement q and set p = 0.  
				q--;
				p = 0;

				// Increment p upwards to q.
				while (p < q) {

					// Swap p and q if the result would produce a larger number
					// than the current n.
					if (digitVecToInt(swap(n, p, q)) > digitVecToInt(n)) {
						n = swap(n, p, q);
					}

					p++;
				}

				// n is now the next smallest number from the originally passed
				// in value.
				found = true;
				break;
			}
			p++;
		}
		
		// We've found n; get out of here.
		if (found) {
			break;
		}

		// Reset p.
		p = 0;

		// Increment q
		q++;
	}

	// Return the numeric form of the found n.
	return digitVecToInt(n);
}

int main() {

	// Initial runs of this program have shown that all pandigitals with 9 and
	// 8 digits are not primes.
	//
	// I've read that if the sum of the digits are divisible by 3, a number may
	// not be prime.  I've not seen a proof as to why though.
	// 9+8+7+6+5+4+3+2+1 = 45 (% 3 = 0)
	//   8+7+6+5+4+3+2+1 = 36 (% 3 = 0)

	unsigned long long n = 7654321;
	while (true) {
		unsigned long long r = next(n);

		// If the number provided is returned by next, we know that there is
		// not a next one.
		if (r == n) {
			break;
		}

		// Check if r is prime.
		if (isPrime(r)) {
			
			// If so, we've found it.
			std::cout << "Largest Pandigital Prime for n-digits: " << r << std::endl;
			break;
		}
		n = r;
	}

	return 0;
}

