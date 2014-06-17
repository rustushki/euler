#include <iostream>
#include <vector>

std::vector<int> primes;

std::vector<int> getPrimeFactors(int n) {
	std::vector<int> primeFactors;
	for (int x = 2; x*x <= n; x++) {
		if (n % x == 0) {
			primeFactors.push_back(x);
			n = n/x;
			x = 1;
		}
	}

	if (n > 1) {
		primeFactors.push_back(n);
	}

	return primeFactors;
}

bool isPrime(int n){
	return (getPrimeFactors(n).size() == 1);
}

std::vector<int> flatten(std::vector<int> vec) {
	// Initialize each potential factor to 0.
	std::vector<int> flattened(100+1, 0);

	// Increment the number of factors in the flattened array
	for (int x = 0; x < vec.size(); x++) {
		flattened[vec[x]]++;
	}

	return flattened;
}

std::vector<int> multiplyEach(std::vector<int> vec, int b) {
	// Multiply each factor by exponent b.
	for (int x = 0; x < primes.size(); x++) {
		vec[primes[x]] *= b;
	}

	return vec;
}

/** Is the vector a already in vector b?
 */
bool isIn(std::vector<int> a, std::vector< std::vector<int> > b) {
	for (int x = 0; x < b.size(); x++) {
		bool found = true;
		for (int y = 0; y < primes.size(); y++) {
			int prime = primes[y];
			if (a[prime] != b[x][prime]) {
				found = false;
				break;
			}
		}
		if (found) {
			return true;
		}
	}
	return false;
}

int main() {

	std::vector< std::vector<int> > factorsOf1;
	std::vector< std::vector<int> > factorsOfX;

	for (int i = 2; i < 100; i++) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
	}

	for (int a = 2; a <= 100; a++) {
		factorsOf1.push_back(flatten(getPrimeFactors(a)));
	}

	int terms = 0;
	for (int b = 2; b <= 100; b++) {
		for (int a = 0; a < factorsOf1.size(); a++) {
			std::vector<int> vec = multiplyEach(factorsOf1[a], b);

			if (!isIn(vec, factorsOfX)) {
				terms++;
				if (terms % 100 == 0) {
				std::cout << terms << std::endl;
				}
				factorsOfX.push_back(vec);
			}
		}
	}

	std::cout << "Number of Terms: " << terms << std::endl;
	
	return 0;
}
