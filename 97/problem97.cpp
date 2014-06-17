#include <iostream>
#include <ctime>

/* Problem 97 - Find the last 10 digits in the non Mersenne prime: 28433 *
 * 2^7830457 + 1.
 *
 * This program finds that number minus 1.
 *
 * The following code a lesson in "solving only what is necessary".  Note that
 * the problem state that we only want the last 10 digits.  My strategy was to
 * take the algorithm used in Problem 56 and adapt it for use in this one.
 * During development, I found that I could save bookus of time by only
 * computing the 10 digits.  That's not bad, but you can do much better.
 *
 * n % 10000000000 will also yield only the last ten digits.  This psuedo code
 * is a far better solution:
 *
 * n = 28433 
 * for x = 1 to 7830457:
 *    n << 1 // multiply by 2.
 *    n %= 10000000000  // constrain n to only the 10 ten digits.
 * n++
 *
 */

/* carryMult - multiply multiplier times each digit in mc to produce mc * mp.
 * Constrain the calculation to n places.  n is not specifiable as a parameter,
 * but is only hard coded to 10.
 */
void carryMult(int* mc, int mp) {
	int* digit = mc;

	int carry = 0;
	int place = 0;

	// Go through each digit.
	while (*digit != -1) {

		// Only continue iterating while we've not reach the maximum position
		// in the number.
		if (place > 10) {

			// If we've exceeded the max position, set that position to -1
			// gtfo.
			*digit = -1;
			return;

		}

		// Multiply the digit in the current place by mp.
		*digit *= mp;

		// Add the carry to the digit.
		*digit += carry;

		// Compute the carry for next time.
		carry = *digit/10;
		
		// Constrain the number in the current position such that it is a
		// digit.
		*digit %= 10;

		// Move to the next position.
		digit++;
		place++;

	}

	// Handle remaining carry.
	while (carry >= 1) {

		// Only continue iterating while we've not reach the maximum position
		// in the number.
		if (place > 10) {

			// If we've exceeded the max position, set that position to -1
			// gtfo.
			*digit = -1;
			return;

		}

		*digit = carry % 10;
		carry /= 10;
		digit++;
	}
	*digit = -1;
}

int main() {

	int ans[12] = {1, -1};

	std::clock_t start = std::clock();

	int power = 7830457;
	for (int x = 0; x < power; x++) {
		carryMult(ans, 2);
	}

	carryMult(ans, 28433);

	std::cout << "Found in: " << ((std::clock() - start) / (double)CLOCKS_PER_SEC) << "s" << std::endl;

	std::cout << ans[9];
	std::cout << ans[8];
	std::cout << ans[7];
	std::cout << ans[6];
	std::cout << ans[5];
	std::cout << ans[4];
	std::cout << ans[3];
	std::cout << ans[2];
	std::cout << ans[1];
	std::cout << ans[0];
	std::cout << " + 1";
	std::cout << std::endl;
	return 0;
}
