#include <iostream>

int table[10];

int sumDigiFact(int n) {
	int sum = 0;
	while (n >= 1) {
		sum += table[n % 10];
		n /= 10;
	}
	return sum;
}

int main() {

	table[0] = 1;
	table[1] = 1;
	table[2] = 2;
	table[3] = 6;
	table[4] = 24;
	table[5] = 120;
	table[6] = 720;
	table[7] = 5040;
	table[8] = 40320;
	table[9] = 362880;

	int total = 0;
	for (int x = 1; x < 1000000; x++) {

		int chainLength = 1;
		int intermediate = x;
		bool repeaterFound = false;
		while (true) {
			if (chainLength > 60) {
				break;
			}

			int last = intermediate;
			intermediate = sumDigiFact(intermediate);

			if (last == intermediate) {
				break;
			} else if (intermediate == 145 || intermediate == 871 || intermediate == 872 || intermediate == 169) {
				if (repeaterFound) {
					break;
				}
				repeaterFound = true;
			}

			chainLength++;
		}

		if (chainLength == 60) {
			total++;
		}

	}
	std::cout << total << std::endl;
	return 0;
}
