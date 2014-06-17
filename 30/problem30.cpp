#include <iostream>
#include <cmath>
int main() {
	
	int power = 5;
	unsigned long long ans = 0;

	// Discover Upper Limit.
	// When the number of places (n) in a number is such that 9^power * n <
	// 10^power, we know that 9^power * n must be the upper limit.  This code
	// is semantically correct, but only works where power <= 18 since power >=
	// 19 will overflow unsigned long long size on a 32 bit OS.
	unsigned long long upperLimit = 1;
	int n = 0;
	do {
		n++;
		upperLimit = pow(9, power)*n;
	} while (upperLimit > pow(10,n));

	std::cout << "Checking Number beneath Upper Limit of " << upperLimit << std::endl;

	// Go throuh all numbers between 10 and the upper limit.  10 is the lower
	// limit because you can't the powers of of a single digit number
	// (according to the problem).
	for (int x = 10; x <= upperLimit; x++) {

		// Examine each digit of the number.
		int n = x;
		int sum = 0;
		while (n >= 1) {
			int digit = n % 10;

			// Raise each digit to the power; sum.
			sum += pow(digit, power);
			n /= 10;
			
			// if the sum is greater than x, break out prematurely.
			if (sum > x) {
				break;
			}
		}

		// If sum is equal to x, the sum of the powers of each digit equals x;
		// add to the grand sum.
		if (sum == x) {
			ans += sum;
			std::cout << x << std::endl;
		}
	}

	// Output answer.
	std::cout << "Answer: " << ans << std::endl;

	return 0;
}
