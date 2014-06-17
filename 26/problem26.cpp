#include <iostream>
#include <vector>

/* getCycleLength - a cycle should be thought of as a sequence where the
 * remainder of the division of a numerator by its denominator equals a number
 * which is either the original numerator -OR- through repeated division will
 * lead back to the original numerator.
 *
 * To discover a sequence, store each numerator in the division sequence.
 * Examine the stack of numerators starting with the most recent and working
 * backwards until the numerator examined equals the most recent numerator.
 * Return the number of numerators counted (inclusively).
 */
int getCycleLength(int n, int d) {

	// Stack numerators here.
	std::vector<int> numerators;

	while (n != 0) {

		// If the numerator is less than the denominator, raise by a power of
		// ten.
		if (d > n) {
			n *= 10;
		}

		// Push the Numerator onto the Stack.
		numerators.push_back(n);

		// Examine all numerators so far to discover a cycle.
		int cycleLen = 0;
		for (int x = numerators.size() - 2; x >= 0; x--) {
			cycleLen++;
			if (n == numerators[x]) {
				return cycleLen;
			}
		}

		// The new numerator is the remainder from the division.
		n = n % d;

	}

	// If we're here, that means that no cycle has been discovered.  Consider a
	// number like 1/2 or 1/4 which have no cycles.
	return 0;

}

int main() {
	int maxD       = 0;
	int maxDDigits = 0;
	for (int d = 2; d <= 1000; d++) {
		int cycleLength = getCycleLength(1, d);
		if (cycleLength > maxDDigits) {
			maxD = d;
			maxDDigits = cycleLength;
		}
	}
	std::cout << "1/d has the longest recurring cycle where d = " << maxD << std::endl;

	return 0;
}
