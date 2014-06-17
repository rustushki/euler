#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

typedef std::vector<short> DIGITVEC;

DIGITVEC intToDigitVec(long n) {
	DIGITVEC dv;
	while (n >= 1) {
		dv.push_back(n % 10);
		n /= 10;
	}
	return dv;
}

bool isInDigitVec(short digit, DIGITVEC & digitVec) {
	for (int x = 0; x < digitVec.size(); x++) {
		if (digitVec[x] == digit) {
			return true;
		}
	}

	return false;
}

// Cheap, not entirely accurate, but fast.
bool isPanDigital(DIGITVEC & digitVec) {
	if (digitVec.size() != 9) {
		return false;
	}

	for (int x = 0; x < digitVec.size(); x++) {
		if (digitVec[x] == 0) {
			return false;
		}
	}

	return true;
}

long digitVecToInt(DIGITVEC & digitVec) {
	long ans = 0;
	for (int x = digitVec.size()-1; x >= 0; x--) {
		ans += digitVec[x] * pow(10, digitVec.size() - 1 - x);
	}
	return ans;
}

int main() {

	std::clock_t start = std::clock();

	DIGITVEC dv;

	long ans = 0;

	for (int x = 1; x <= 10000; x++) {

		bool notFound = false;

		for (int n = 1; n <= 20; n++) {
			
			long p = (long)x*n;
			if (p <= 987654321) {

				DIGITVEC pDv = intToDigitVec(p);
				while(pDv.size()) {
					short digit = pDv.back();
					pDv.pop_back();
					if (isInDigitVec(digit, dv)) {
						notFound = true;
						break;
					} else {
						dv.push_back(digit);
					}
				}

			}
		
			if (notFound) {
				break;
			} else {
				if (n != 1) {
					if (isPanDigital(dv)) {
						if (digitVecToInt(dv) > ans) {
							std::cout << digitVecToInt(dv) << " : " << x << ", " << n << std::endl;
							ans = digitVecToInt(dv);
						}
					}
				}
			}
		}

		dv.clear();
	}

	std::cout << "Found in: " << ((std::clock() - start) / (double)CLOCKS_PER_SEC) << "s" << std::endl;

	
	return 0;
}
