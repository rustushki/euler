#include <iostream>
#include <cmath>

int main() {

	int N = 1;
	int D = 1;

	for (int x = 10; x < 100; x++) {

		if (x % 10 == 0) {
			continue;
		}

		for (int y = x+1; y < 100; y++) {
			if (y % 10 == 0) {
				continue;
			}

			short n1 = x / 10;
			short n2 = x % 10;

			short d1 = y / 10;
			short d2 = y % 10;

			double result = (double)x/y;

			bool found = false;

			if (n1 == d1 && !found) {
				double simp = ((double)n2/d2);

				if (simp == result) {
					N *= n2;
					D *= d2;
					found = true;
				}


			}

			if (n2 == d1 && !found) {
				double simp = (double)n1/d2;

				if (simp == result) {
					N *= n1;
					D *= d2;
					found = true;
				}


			}

			if (n1 == d2 && !found) {
				double simp = (double)n2/d1;

				if (simp == result) {
					N *= n2;
					D *= d1;
					found = true;
				}

			}

			if (n2 == d2 && !found) {
				double simp = (double)n1/d1;

				if (simp == result) {
					N *= n1;
					D *= d1;
					found = true;
				}
			}

			if (found) {
				std::cout << x << "/" << y << "=" << result << std::endl;
			}

		}
	
	}

	std::cout << "Unsimplified answer:" << std::endl;
	std::cout << N << "/" << D << "=" << (double)N/D << std::endl;
	std::cout << "Simplify fraction to obtain final result." << std::endl;

	return 0;
}
