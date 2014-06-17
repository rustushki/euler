#include <iostream>
#include <vector>
#include <set>

/* isPandigitalTriple - examine the digits in m, n and p.  if each digit 1-9 is
 * represent in one of m,n,p, return true.  if 0 is in m,n or p, return false.
 * if duplicate digits are in m,n,p return false.
 */
bool isPandigitalTriple(int m, int n, int p) {
	std::vector<short> digits;

	int d;

	// Examine m
	while (m >= 1) {
		d = m % 10;
		m /= 10;

		if (d == 0) {
			return false;
		}

		for (int x = 0; x < digits.size(); x++) {
			if (digits[x] == d) {
				return false;
			}
		}

		digits.push_back(d);
	}

	// Examine n
	while (n >= 1) {
		d = n % 10;
		n /= 10;

		if (d == 0) {
			return false;
		}

		for (int x = 0; x < digits.size(); x++) {
			if (digits[x] == d) {
				return false;
			}
		}

		digits.push_back(d);
	}

	// Examine p
	while (p >= 1) {
		d = p % 10;
		p /= 10;

		if (d == 0) {
			return false;
		}

		for (int x = 0; x < digits.size(); x++) {
			if (digits[x] == d) {
				return false;
			}
		}

		digits.push_back(d);
	}

	return (digits.size() == 9);

}

int main() {

	/*
	Given that the digits of the multiplicand, multiplier and product must be
	pandigital, we can infer that:

	 1. it is not possible to have a product of a single digit. n*m > 9 since m
	 and n are both greater than 9 themselves.
	 
	 2. it is not possible to have a product of two digits.  n*m > 99 since
	 both m and n are greater than 99.

	 3. it is not possible to have a product of three digits.  n*m > 999 since
	 either m and n are minimally 3 digits which leads to a product of 5 to 6
	 digits

	 4. neither m nor n can be greater than 4 digits in size.  if one has 5
	 digits or more, the other minimally must have 1 digit. a one digit number
	 times a 5 digits numbe will lead to a 5 or 6 digit product.  the count of
	 the digits total will be 10 or 11, which is greater than 9.

	 5. we only need to examine n's smaller than m.  since for every n,m and p
	 where n*m==p, n and m can be flipped and the statement is still true.

	T/f:

	 we need only examine
	  m = 9999 to 100
	   where n = 1 to 9 when m >= 1000
			 n = 10 to 99 when m >= 100 && m < 1000

	 for each set m, n and p where m*n == p,

	  determine if the digits of m, n and p are pandigital.
	  if so, add to the sum.
	
	This formula does not sieve out non-uniques; but doing so is trivial by
	using a set.
	*/

	std::set<int> products;

	for (int m = 100; m <= 9999; m++) {

		int high = 9;

		if (m < 1000) {
			high = 99;
		}
		
		for (int n = 1; n <= high; n++) {
				
			int p = m*n;

			if (isPandigitalTriple(m,n,p)) {
				
				products.insert(p);

				std::cout << m << "*" << n << "=" << p << std::endl;

			}

		}

	}


	// Get the sum of the unique products.
	std::set<int>::iterator it;

	int sum = 0;
	for (it=products.begin(); it != products.end(); it++) {
		sum += *it;
	}

	// Output it.
	std::cout << sum << std::endl;
	return 0;
}
