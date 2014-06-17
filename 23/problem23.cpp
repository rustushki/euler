#include <iostream>
#include <vector>
#include <algorithm>

int getDivisorSum(int n) {

	int sum = 0;
	for (int x = 1; x <= n/2; x++) {
		if (n % x == 0) {
			sum += x;
		}
	}

	return sum;
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

	std::vector<int> expressableSums;
	for (int y = 0; y < abundantNums.size(); y++) {
		for (int z = y; z < abundantNums.size(); z++) {
			int sum = abundantNums[y] + abundantNums[z];
			if (sum <= 20161) {
				expressableSums.push_back(sum);
			} else {
				break;
			}
		}
	}
	std::cout << "Total Pair Sums Of Abundant Numbers: " << expressableSums.size() << std::endl;

	sort(expressableSums.begin(), expressableSums.end());

	std::cout << "Sorted" << std::endl;

	int sumOfUnexpressable = 0;
	for (int x = 0; x <= 20161; x++) {

		// Perform a Binary Search on the List of Sums of Abundant Numbers.
		bool isExpressable = false;
		int l = 0;
		int h = expressableSums.size()-1;
		while (h >= l) {
			int m = (h+l)/2;

			int thisSum = expressableSums[m];

			//if (x == 24) std::cout << thisSum << "(" << m << ")" << std::endl;

			if (thisSum == x) {
				isExpressable = true;
				break;
			} else if (x > thisSum) {
				l = m + 1;
			} else if (x < thisSum) {
				h = m - 1;
			}
		}

		if (!isExpressable) {
			sumOfUnexpressable += x;
			//std::cout << x << ":  No" << std::endl;
		} else {
			//std::cout << x << ": Yes" << std::endl;
		}
	}

	std::cout << "Sum of Unexpressable       : " << sumOfUnexpressable  << std::endl;
	return 0;
}
