#include <iostream>
#include <cmath>
#include <vector>

// A dictionary of prime numbers.
std::vector<int> primeDict;

// How many primes to add to the prime dictionary.
const int MAX = 1075;


// This isPrime function uses the prime dictionary to speed itself up.
bool isPrime(int n) {

	// 0 and 1 are not prime, 2 is.
	if (n <= 2) {
		if (n == 2) {
			return true;
		}

		return false;
	}

	// Even numbers > 2 are not prime.
	if (n % 2 == 0) {
		return false;
	}

	// Search the prime dictionary. If the number is divisible by a number in
	// the prime dictionary, it is not prime.
	int x;
	for (x = 0; x < primeDict.size() && primeDict[x] <= sqrt(n); x++) {
		if (n % primeDict[x] == 0) {
			return false;
		}
	}


	// Prevent overrunning the prime dictionary.
	if (x >= primeDict.size() && x != 0) {
		x = primeDict.size() - 1;
	}

	int y;
	if (primeDict.size() <= 1) {
		y = 3;
	} else {
		y = primeDict[x];
	}


	// Check all odds between the end of the prime dictionary and the square
	// root of n.  If n is divisible by any of those, n is not prime.
	for ( ; y <= sqrt(n); y += 2) {
		if (n % y == 0) {
			return false;
		}
	}

	// Otherwise, n is prime.
	return true;
}

// Build the prime number dictionary.
void buildPrimeDict() {

	primeDict.clear();
	// Note that this implemenatation explicitly skips the Prime Number 2.
	//primeDict.push_back(2);
	for (int c = 0, x = 3; c < MAX; x += 2) {
		if (isPrime(x)) {
			primeDict.push_back(x);
			c++;
		}
	}

}

// Concatenate two integers.
int concat(int x, int y) {
	int c = 0;
	int p = 0;

	while (y >= 1) {
		int d = y % 10;
		p *= 10;
		if (p == 0) {
			p = 1;
		}
		c += d * p;
		y /= 10;
	}

	while (x >= 1) {
		int d = x % 10;
		p *= 10;
		if (p == 0) {
			p = 1;
		}
		c += d * p;
		x /= 10;
	}

	return c;
}

// Concatenate x and y as xy and yx.  Check if each is prime.  Return true if
// so.
bool primeBothWays(int x, int y) {
	x = primeDict[x];
	y = primeDict[y];
	if (!isPrime(concat(x, y))) {
		return false;
	}

	if (!isPrime(concat(y, x))) {
		return false;
	}

	return true;
}

int main() {

	buildPrimeDict();

	for (int v = 0; v < MAX; v++) {
	for (int w = v+1; w < MAX; w++) {
	if (primeBothWays(w, v)) {

	for (int x = w+1; x < MAX; x++) {
	if (primeBothWays(x, w) && primeBothWays(x, v)) {

	for (int y = x+1; y < MAX; y++) {
	if (primeBothWays(y, x) && primeBothWays(y, w) && primeBothWays(y, v)) {

	for (int z = y+1; z < MAX; z++) {
	if (primeBothWays(z, y) && primeBothWays(z, x) && primeBothWays(z, w) && primeBothWays(z, v)) {
		std::cout        << primeDict[v];
		std::cout << "," << primeDict[w];
		std::cout << "," << primeDict[x];
		std::cout << "," << primeDict[y];
		std::cout << "," << primeDict[z];
		std::cout << std::endl;

		std::cout << "sum = " << primeDict[v]+primeDict[w]+primeDict[x]+primeDict[y]+primeDict[z];
		return 0;

	}}}}}}}}}

	return 0;
}
