#include <iostream>
#include <vector>

// The largest number involved here has ~379 digits.  I discovered this through
// experimentation.
#define SIZE 379

typedef std::vector<short> INT;

/* Problem 57 - 
 * 
 * 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) ~ sqrt(2).
 *
 * You can approximate sqrt(2) by computing the filling in the ellipsis with 0
 * after a number of iterations.  The higher the iterations, the closer the
 * approximation of sqrt(2).
 *
 * The approximation can be simplified down to a numerator and a denominator.
 * The numerator will always be bigger than the denominator, and consequently
 * will have the same number of digits or more than the denominator.
 *
 * This problem asks how many approximations have numerator larger than the
 * denominator.
 *
 * The key to this problem is to compute the endless fraction first, then to
 * add 1 to later.
 *
 * This program was almost a disaster until I figured out the Secret Sauce.
 * See main() for details.
 */

/*******************************************************************************
 * print - print a given vector int to the console.
 */
void print(INT c) {
	bool firstDigitFound = false;
	for (int p = c.size()-1; p >= 0; p--) {

		if (!firstDigitFound) {
			if (c[p] != 0) {
				firstDigitFound = true;
			}
		}

		if (firstDigitFound) {
			std::cout << c[p];
		}
	}
}

/*******************************************************************************
 * add - add two vector ints.  Implements a carry adder like you learned in the
 * third grade.  Return the result.
 */
INT add(INT a, INT b) {


	INT sum(SIZE, 0);

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
	INT product(SIZE, 0);

	/* Inefficient, but code complete implementation of mult.
	for (int x = 0; x < b; x++) {
		product = add(product, a);
	}
	*/

	// More efficient (but still not extremely fast) implementation.
	int place = 0;
	while (b >= 1) {

		INT temp(SIZE, 0);

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

int main() {
	
	int count = 0;

	// Initialize the fraction so that it is equal to 1/(2+0) or one half.
	INT num(SIZE,0);
	num[0] = 1;
	INT den(SIZE,0);
	den[0] = 2;

	// Go through each approximation where i = 1 is the first and i= 1000 is
	// the last.
	for (int i = 1; i <= 1000; i++) {

		// Add 2 to the fraction.
		// 
		// More precisely:
		//    Multiply the denominator by 2 and add the result to the
		//    numerator.  Or: n = 2*d; 
		INT temp1 = den;
		temp1 = mult(temp1, 2);
		num = add(num, temp1);

		// Divide 1 by this fraction.
		//
		// More precisely:
		//    Swap the numerator and the denominator. Or: 1 / (n/d).
		INT temp2 = den;
		temp2 = den;
		den = num;
		num = temp2;

		// Secret Sauce:
		// Pretend we add 1 to the current fraction.
		// Not actually adding 1 allows us to use the un-adulterated result in
		// the next approximation.
		INT tempNum = add(den, num);

		// Iterate through each digit to determine whether the numerator has
		// more digits than the denominator.
		for (int x =  den.size()-1; x >= 0; x--) {
			if (tempNum[x] != 0 && den[x] == 0) {
				count++;
				break;
			} else if (tempNum[x] != 0 && den[x] != 0) {
				break;
			}
		}
	}

	// Output the total number of approximations where the numerator is larger
	// than the denominator.
	std::cout << count << std::endl;

	return 0;
}
