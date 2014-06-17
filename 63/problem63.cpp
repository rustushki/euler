#include <iostream>
#include <cmath>

/* Problem 63 -
 *
 * Find the count of all number n^p where n and p are integers and n^p has p
 * digits.
 *
 */

int main() {

	// Count the number of p-digit numbers of the form n^p in 'count'
	//
	// Disregard Special Case:
	//   0^1 has 1 digit, so p == 1. 0^x where x > 1 also has 1 digit is < p.
	//  
	//   Unfortunately, log10(0) is undefined and my algorithm above doesn't
	//   work for it.  Manually count it in here.
	//
	// Upon further inspection, Project Euler consider 0 not to count as a
	// Natural Number and t/f it shouldn't be included.  My missing power was
	// 1^1 which is solved by modifying the test so than p-1 < log10(n) <= p.
	int count = 0;

	// Try out each power.  Don't bother with p=0 since log10(0) is undefined.
	// Don't bother with p > 21 since 9^22 has 21 digits and t/f all powers
	// higher than 21 for n will also only have < p digits.
	for (int p = 1; p <= 21; p++) {

		// Any n greater than 9 will always have at least 1 digit more than p.
		// Don't bother evaluating any n's greater than 9.
		for (int n = 1; n <= 9; n++) {
			float test = log10(n);
			test *= (float)p;

			// Special Sauce:
			// if p-1 < log10(n)*p < p then n^p must have p digits where p != 0.
			if (test > (float)p-1 && test <= p) {
				count++;
				//std::cout << n << "^" << p << std::endl;
			}
		}
	}

	count++;

	std::cout << count << std::endl;
	
	return 0;
}
