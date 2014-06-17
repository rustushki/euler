#include <iostream>
#include <vector>
#include <cmath>

/* Problem 44 - 
 * 
 * Find the Pk and Pj where Pk+Pj is pentagonal, Pk-Pj is pentagonal, Pk and Pj
 * are pentagonal and the |Pk-Pj| is minimized.  The answer is the minimized
 * |Pk-Pj|.
 *
 */

std::vector<unsigned long long> pentagonals;


/***************************************************************
 * getPentagonal - get the nth pentagonal number.  note that the limit is
 * sizeof(unsigned long long) for the correctness of this function.
 */
unsigned long long getPentagonal(int n) {

	// Formula for determining the nth pentagonal number.
	return n * (3*n-1) / 2;

}

/***************************************************************
 * generatePentagonals - generates a sequence of 'count' pentagonal numbers and
 * stores them in a global vector called pentagonals.  Use this vector later as
 * a lookup table.
 */
void generatePentagonals(int count) {

	pentagonals.clear();

	for (int x = 1; x <= count; x++) {
		pentagonals.push_back(getPentagonal(x));
	}

}

/***************************************************************
 * isPentagonal - determine if a number 'x' is a pentagonal number.  return
 * true if so, false otherwise.
 */
bool isPentagonal(int x) {

	// If x is pentagonal:
	// x = n(3*n-1)/2.
	// 0 = n(3*n-1)/2 - x.
	//  a = 3/2
	//  b = -1/2
	//  c = -x
	// Using Quadratic Formula, we can show that:
	double n = (.5 + sqrt(.25 + 6*x))/3;

	// If n is an integer, then x must be pentagonal.
	return (n == (int)n);
}

int main() {

	// Generate a lookup table of 'count' pentagonal numbers.  After
	// experimentation, I found that 2500 pentagonals was the right 'ball
	// park' for determining the answer to this problem.
	int count = 2500;
	generatePentagonals(count);


	// The Minimized Difference between two Pentagonal Numbers which meet the
	// criteria for the answer.
	unsigned long long minDiff = pentagonals.back();


	// Iterate over each distinct pair of pentagonals from smallest to biggest.
	for (int x = 0; x < count; x++) {
		for (int y = x+1; y < count; y++) {

			// Read these pentagonals from the lookup table.
			unsigned long long pX = pentagonals[x];
			unsigned long long pY = pentagonals[y];

			// Get difference between them.
			unsigned long long diff = pY - pX;

			// Secret Sauce #1:
			// Only check if diff and sum are pentagonal if the diff is less
			// than the Minimized Diff so far.
			if (diff < minDiff) {
				
				// Py - Px must be pentagonal.
				if (isPentagonal(diff)) {

					// Py + Px must be pentagonal.
					unsigned long long sum = pY + pX;
					if (isPentagonal(sum)) {

						// Lower the Minimized Diff and Output.
						// The last line of output is the answer.
						std::cout << diff << std::endl;
						minDiff = diff;

					}
				}
			
			// Secret Sauce #2:
			// If Py - Px is already larger than the Minimized Diff; as Py
			// continues to ascend the diff will get even bigger.  Go ahead and
			// break out so we can move to the next Px.
			} else {
				break;
			}
		}
	}

	return 0;
}
