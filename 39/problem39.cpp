#include <iostream>
#include <cmath>

// I'm not very happy with this.  It runs in between 15 and 30 seconds.  I hope
// that more pythagorean problems will expose the flaw in my logic.
//
// Even an n^3 loop search a, b and c are faster on machines from 7 years ago. :-(
int main() {

	// Perimeter P where Maximum Number of Pythagorean Triples Exist
	int pMax      = 0;

	// Number of Pythagorean Triples for pMax
	int pMaxCount = 0;
	
	// Search Integral Sided Right Triangles with Perimeter P.
	// Note that P = 12 is the smallest Integral Sided Right Triangle (A=3, B=4, C=5)
	for (int p = 12; p <= 1000; p++) {

		// Number of Solutions {A,B,C} for p.
		int count = 0;
		
		// Search for Hypotenuse C where A^2+B^2 == C^2 for some A and B.
		// Note that C can't be more than p/2, else C > A+B which violates
		// Pythagorean Thm.
		for (int C = p/2; C >= 1; C--) {

			// O(N^2) Search for A and B.
			// Note that A and B are both independently < C by Pythagorean Thm.
			for (int A = sqrt(p)+1; A < C; ++A) {
				for (int B = C-A+1; B < C; ++B) {

					if (A+B+C > p) {
						break;
					}

					// By Pythag. Thm, A+B is greater than C.
					// Don't do more expensive check of A^2+B^2 == C^2
					if (A+B+C != p) {
						continue;
					}

					if (A*A + B*B == C*C) {
						++count;
					}

				}
			}
			
		}

		if (count > pMaxCount) {
			pMaxCount = count;
			pMax = p;
			std::cout << pMax << "; count = " << pMaxCount << std::endl;
		}

	}

	std::cout << pMax << std::endl;

	return 0;
}
