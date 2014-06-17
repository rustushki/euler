#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

// Set of constants to denote a type of number or number test.
enum Poly {
	  TRI = 0
	, SQU = 1
	, PEN = 2
	, HEX = 3
	, HEP = 4
	, OCT = 5
};

// Test to determine if a number is triangular.
bool isTri(int c) {
	float f = sqrt(1 + 8*c);
	if (f - (int)f == 0) {
		return true;
	}
	
	return false;
}

// Test if a number is square.
bool isSqu(int c) {
	float f = sqrt(c);
	if (f - (int)f == 0) {
		return true;
	}
	
	return false;
}

// Test if a number is pentagonal.
bool isPen(int c) {
	float f = sqrt(1 + 24*c);
	if (f - (int)f == 0) {
		return ((1 + (int)f) % 6 == 0);
	}
	return false;
}

// Test if a number is hexagonal.
bool isHex(int c) {
	float f = sqrt(1 + 8*c);
	if (f - (int)f == 0) {
		return ((((int)f + 1) % 4) == 0);
	}
	return false;
}

// Test if a number is heptagonal.
bool isHep(int c) {
	float f = sqrt(9 + 40*c);
	if (f - (int)f == 0) {
		return ((3 + (int) f) % 10 == 0);
	}
	return false;
}

// Test if a number is octagonal.
bool isOct(int c) {
	float f = sqrt(4 + 12*c);
	if (f - (int)f == 0) {
		return ((2 + (int) f) % 6 == 0);
	}
	return false;
}

// Test if a number is polygonal where the sides of the polygon is 3 >= x <= 8
bool isPolygonal(int a) {
	if (isTri(a)) {
		return true;
	}

	if (isSqu(a)) {
		return true;
	}

	if (isPen(a)) {
		return true;
	}

	if (isHex(a)) {
		return true;
	}

	if (isHep(a)) {
		return true;
	}

	if (isOct(a)) {
		return true;
	}
	return false;
}

// Given a list of n 4-digit numbers and a list of polygon tests, decide
// whether each of the tests individual passes with the n numbers.
bool allReppedReal(std::vector<int> nums, std::vector<Poly> polyTests) {

	if (nums.size() == 0) {
		return true;
	}

	int q = nums.back();
	nums.pop_back();

	std::vector<Poly>::iterator i;

	i = std::find(polyTests.begin(), polyTests.end(), TRI);
	if (i != polyTests.end()) {
		if (isTri(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(TRI);
		}
	}

	i = std::find(polyTests.begin(), polyTests.end(), SQU);
	if (i != polyTests.end()) {
		if (isSqu(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(SQU);
		}
	}

	i = std::find(polyTests.begin(), polyTests.end(), PEN);
	if (i != polyTests.end()) {
		if (isPen(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(PEN);
		}
	}

	i = std::find(polyTests.begin(), polyTests.end(), HEX);
	if (i != polyTests.end()) {
		if (isHex(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(HEX);
		}
	}

	i = std::find(polyTests.begin(), polyTests.end(), HEP);
	if (i != polyTests.end()) {
		if (isHep(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(HEP);
		}
	}

	i = std::find(polyTests.begin(), polyTests.end(), OCT);
	if (i != polyTests.end()) {
		if (isOct(q)) {
			polyTests.erase(i);
			if (allReppedReal(nums, polyTests)) {
				return true;
			}
			polyTests.push_back(OCT);
		}
	}

	return false;
}

// a - f create 6 4 digit numbers of the form:
//   aabb
//   bbcc
//   ccdd
//   ddee
//   eeff
//   ffaa
//
// Test each of those numbers to confirm that each of the polygonal tests is
// represented by them.
bool allRepped(int a, int b, int c, int d, int e, int f) {
	std::vector<int> nums;
	nums.push_back(a*100+b);
	nums.push_back(b*100+c);
	nums.push_back(c*100+d);
	nums.push_back(d*100+e);
	nums.push_back(e*100+f);
	nums.push_back(f*100+a);

	std::vector<Poly> polyTests;
	polyTests.push_back(TRI);
	polyTests.push_back(SQU);
	polyTests.push_back(PEN);
	polyTests.push_back(HEX);
	polyTests.push_back(HEP);
	polyTests.push_back(OCT);
	return allReppedReal(nums, polyTests);
}


int main() {

	// Generate a 24 digit sequence of the form:
	//  aabbbbccccddddeeeeffffaa
	// Each sequence generated matching the 4 digit, cyclic property.  Then
	// test each sequence to see if each polygonal test is represented in each
	// for digit number.
	for (int a = 10; a <= 99; a++) {
		for (int b = 10; b <= 99; b++) {
			if (isPolygonal(a*100+b)) {
			for (int c = 10; c <= 99; c++) {
				if (isPolygonal(b*100+c)) {
				for (int d = 10; d <= 99; d++) {
					if (isPolygonal(c*100+d)) {
					for (int e = 10; e <= 99; e++) {
						if (isPolygonal(d*100+e)) {
						for (int f = 10; f <= 99; f++) {
							if (isPolygonal(e*100+f) && isPolygonal(f*100+a)) {
								if(allRepped(a, b, c, d, e, f)) {
									printf("%02d%02d%02d%02d%02d%02d%02d%02d%02d%02d%0d%0d\n", a, b, b, c, c, d, d, e, e, f, f, a);
									std::cout << a*100+b + b*100+c + c*100+d + d*100+e + e*100+f + f*100+a << std::endl;
									return 0;
								}
							}
						}
					}
					}
				}
				}
			}
			}
		}
		}
	}
	return 0;
}
