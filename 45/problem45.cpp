#include <iostream>
#include <cmath>

/* getHexagonal - Given an integer, find it's number in the sequence of
 * hexagonal numbers.
 */
unsigned long long getHexagonal(int n) {
	return n*(2*n-1);
}

/* isTriangle - an improved version of is triangle which relies on C's sqrt
 * function.  Very quickly determines if a number is a triangle number.
 */
bool isTriangle(unsigned long long n) {
   // If 8*n + 1 is a Perfect Square, then n must be a triangle number.
	int discriminant = (int)sqrt(8*n+1);
	return (discriminant == (double)sqrt(8*n+1));
}

/* isPent - very quickly determines if a number is a pentagonal number.
 */
bool isPent(unsigned long long n) {
	int discriminant = (int)sqrt(1+24*n);
	if (discriminant == (double)sqrt(1+24*n)) {
		return ((discriminant+1) % 6 == 0);
	}
}

int main() {

	// Starting with the last known pentagonal number which is also triangular
	// and hexagonal...
	int h = 143; 
	unsigned long long hN;

	// Iterate through the subsequent hexagonal numbers ...
	do {
		h++;
		hN = getHexagonal(h);

	// If the number is a pentagonal number, end loop.
	// I discovered after the fact that all hexagonal numbers are also
	// triangular numbers as well.  No need to check if it's a triangle number.
	} while (!isPent(hN)); // || !isTriangle(hN));

	std::cout << "hN = " << hN << std::endl;
	return 0;
}
