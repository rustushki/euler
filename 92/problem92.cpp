#include <iostream>
#include <vector>

/* Problem 92 -
 *
 * If you apply a function f(x) recursively to any x, it will lead to either 1
 * or 89.  let f(x) be the function which returns the sum of the squares of
 * each digit in x.
 *
 * How many numbers beneath 10,000,000 will reach 89?
 */


/********************************************************
/* sumOfSquaredDigits - return the sum of the square of each digit in a number.
 */
int sumOfSquaredDigits(int n) {

	int sum = 0;

	// Iterate over each digit.
	while (n >= 1) {

		// Get the first digit.
		short digit = n % 10;

		// Add the power to the sum.
		sum += digit * digit;

		// Get the next digit.
		n /= 10;
	}

	// Return the sum.
	return sum;
}

int main() {

	// Count the Total number of numbers less than 10,000,000 which will lead
	// to 89 when f(x) is applied repeatedly.
	int count = 0;

	// Iterate over each number n.
	for (int n = 1; n < 10000000; n++) {

		// Use n for the initial number.
		int next = n;

		// We can safely assume that every number will end this loop :-)
		while (true) {

			// Get the sum of the square of each digit of the next number.
			next = sumOfSquaredDigits(next);

			// If the result is any of these number, add to our total count.
			if (next == 89 || next == 145 || next == 42 || next == 20 || next == 4 || next == 16 || next == 37 || next == 58 || next == 85) {
				count++;
				break;

			// If it's any of these numbers, the final number will be 1 so we
			// can break.
			} else if (next == 1 || next == 44 || next == 32 || next == 13 || next == 10) {
				break;
			}
		}
	}

	// Output the result.
	std::cout << count << std::endl;


	return 0;
}
