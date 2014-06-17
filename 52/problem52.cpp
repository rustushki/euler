#include <iostream>
#include <cmath>
#include <vector>

/* hasSameDigits - Do x and y have the same digits?  If so return true, else
 * false.
 */
bool hasSameDigits(int x, int y) {

	// Build a vector of the digits in x
	std::vector<short> xV;
	while (x >= 1) {
		xV.push_back(x % 10);
		x /= 10;
	}

	// Build a vector of the digits in y
	std::vector<short> yV;
	while (y >= 1) {
		yV.push_back(y % 10);
		y /= 10;
	}

	// Don't bother comparing the vectors if they are not the same size.
	if (xV.size() == yV.size()) {

		// Remove matching elements from xV and yV until xV is empty (and thus
		// yV is empty too)
		while(xV.size() > 0) {

			// Iterate over yV until the element is equal to xV[0]
			bool found = false;
			for (int m = 0; m < yV.size(); m++) {
				
				// If both elements match, remove them and exit loop.
				if (xV[0] == yV[m]) {
					xV.erase(xV.begin() + 0);
					yV.erase(yV.begin() + m);
					found = true;
					break;
				}

			}

			// If the element is not found, they integers don't contain the
			// same digits.
			if (!found) {
				return false;
			}
		}

	// If the ints don't contain the same number of digits, they don't contain
	// the same digits either.
	} else {
		return false;
	}

	// If we're here, the vectors must match.
	return true;
}


int main() {
	
	// Have faith that the answer will be found and that the processor will not
	// be clogged forever
	int x = 1;
	while (true) {

		// m is the multiplicand.
		// m from 6 to 2.  does x * m have the same digits as x?
		bool found = true;
		for (int m = 6; m >= 2; m--) {
			if (!hasSameDigits(x, m*x)) {
				found = false;
				break;
			}
		}

		// If all have the same digits as x, print and break out.
		if (found) {
			std::cout << x << std::endl;
			break;
		}

		// Next x.
		++x;
	}

	return 0;
}
