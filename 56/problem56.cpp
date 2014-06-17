#include <iostream>
#include <vector>

typedef std::vector<short> INT;

/* Problem 56.  Find the max digital sum for a^b where a, b < 100.
 *
 * Implements add, mult and pow for very large unsigned integers (max 200
 * digits).
 *
 */ 

/*******************************************************************************
 * print - print a given vector int to the console.
 */
void print(INT c) {
	for (int p = c.size()-1; p >= 0; p--) {
		std::cout << c[p];
	}
	std::cout << std::endl;
}

/*******************************************************************************
 * digitSum - sum the digits for a given vector int.
 */
int digitSum(INT c) {
	int sum = 0;
	for (int p = c.size()-1; p >= 0; p--) {
		sum += c[p];
	}
	return sum;
}

/*******************************************************************************
 * add - add two vector ints.  Implements a carry adder like you learned in the
 * third grade.  Return the result.
 */
INT add(INT a, INT b) {


	INT sum(200, 0);

	short carry = 0;
	for (int p = 0; p < b.size(); p++) {

		sum[p] = a[p] + b[p] + carry;

		carry = 0;
		if (sum[p] > 9) {
			carry = sum[p] / 10;
			sum[p] %= 10;
		}
	}

	return sum;

}

/*******************************************************************************
 * mult - multiply the vector int by the provided short.  This implementation
 * is equivalent to what you learned in the 3rd grade.  It's also fairly
 * efficient.  There is probably a better way to do this that what I have.
 */
INT mult(INT a, short b) {
	INT product(200, 0);

	/* Inefficient, but code complete implementation of mult.
	for (int x = 0; x < b; x++) {
		product = add(product, a);
	}
	*/

	// More efficient (but still not extremely fast) implementation.
	int place = 0;
	while (b >= 1) {

		INT temp(200, 0);

		// Current Digit.
		short digit = b % 10;
	
		// Multiply the multiplicand (a) by the multiplier (b) at the given
		// place (place).
		int carry = 0;
		for (int x = 0; x < a.size(); x++) {
			int idx = x+place;
			temp[idx] = a[x] * digit + carry;
			carry = temp[idx]/10;
			temp[idx] %= 10;
		}


		product = add(product, temp);

		// Truncate off the current digit.
		b /= 10;

		// Increment place; i.e. tens place, hundreds place.
		place++;
	}

	return product;
}

/*******************************************************************************
 * pow - raise base to the power specified.  Return a vector int result. Uses
 * mult() to repeatedly apply powers.*/
INT pow(short base, short power) {

	// Initialize the result vector int.
	INT c(200, 0);
	c[0] = 1;

	// Repeatedly use mult to multiply base against the result.  Do so for as
	// many powers as we must raise the base.
	while(power > 0) {
		c = mult(c, base);
		power--;
	}

	return c;
}

int main() {

	// Maximum Digital Sum (so far)
	int maxDigitalSum = 0;


	// Iterate through bases as a.
	for (int a = 99; a >= 2; a--) {

		// Debug Output.
		std::cout << a << " ";
		std::cout << std::endl;

		// Iterate through powers as b.
		for (int b = 99; b >= 2; b--) {

			// Compute a^b and sum the digits.
			int ds = digitSum(pow(a, b));

			// If the digital sum is greater than the maximum so far,
			if (ds > maxDigitalSum) {

				// Set the max digital sum.
				maxDigitalSum = ds;

				// Useful debug output.
				std::cout << "\t " << b << ": " << maxDigitalSum;
				std::cout << std::endl;
				print(pow(a, b));
			}
		}
	}

	std::cout << "Max Digital Sum: " << maxDigitalSum << std::endl;

	return 0;
}
