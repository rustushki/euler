#include <iostream>
#include <vector>
#include <algorithm>

// Faster version.


// First improvement is getDivisorSum.
// I don't understand this function, but it has something to do with finding
// divisors around squares smaller than the square root of n.
int getDivisorSum(int n) {
	int num = n;
	int prod=1;
	for(int k=2; k*k<=n; ++k) {
		int p=1;
		while(n % k == 0) {
			p = p*k+1;
			n /= k;
		}
		prod *= p;
	}
	if(n>1)
		prod *= 1+n;
	prod -= num;
	return prod;
}

bool isAbundant(int n) {
	return (getDivisorSum(n) > n);
}
 
int main() {
	
	std::vector<int> abundantNums;
	for (int x = 1; x <= 20161; x++) {
		if (isAbundant(x)) {
			abundantNums.push_back(x);
		}
	}
	std::cout << "Total Abundant Nums < 20161: " << abundantNums.size() << std::endl;

	// Second improvement is to store whether or not a given number may be
	// expressed as a sum of two abundant numbers in constant space.  You can
	// then random access that space later on, using the key as the value to
	// sum in.
	bool expressableSums[20161+1] = {false};
	for (int y = 0; y < abundantNums.size(); y++) {
		for (int z = y; z < abundantNums.size(); z++) {
			int sum = abundantNums[y] + abundantNums[z];
			if (sum <= 20161) {
				expressableSums[sum] = true;
			}
		}
	}

	int sum = 0;
	for (int y = 0; y <= 20161; y++) {
		if (!expressableSums[y]) {
			sum += y;
		}
	}

	// Third improvement.  Better grammar. :-)
	std::cout << "Sum of Inexpressable: " << sum  << std::endl;
	return 0;
}
