#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

std::vector<std::string> AllPerms(int numDigits) {
	std::vector<std::string> perms;

	if (numDigits > 0) {
		perms = AllPerms(numDigits-1);
	}

	if (numDigits == 0) {
		perms.push_back("0");
		return perms;
	}

	char digit = (char)(numDigits + 0x30);

	std::vector<std::string> newPerms;
	for (int x = 0; x < perms.size(); x++) {
		for (int y = 0; y <= perms[x].length(); y++) {
			std::string p = perms[x];
			p.insert(y, 1, digit);
			newPerms.push_back(p);
		}
	}

	return newPerms;
}

int main() {

	int numDigits = 9;
	clock_t start = clock();
	std::vector<std::string> perms = AllPerms(numDigits);

	std::cout << clock() - start << std::endl;
	sort(perms.begin(), perms.end());
	std::cout << clock() - start << std::endl;

	std::cout << perms[1000000-1] << std::endl;
	std::cout << clock() - start << std::endl;

	return 0;
}
