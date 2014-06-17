#include <iostream>

/* Problem 76
 * 
 * I really struggled with this one.  It took 3 to 6 weeks for me to solve it.
 *
 * How many ways can you add two or more positive integers to equal 100?  Let's
 * tweak that question a bit.  Instead, How many ways can you add one or more
 * positive integers less than 100 to equal 100?
 *
 * Let's answer the question for 5 instead of 100.
 *
 * f(5, 4) =
 *	 4 + r = 5; r = 1
 *	 3 + r = 5; r = 2
 *	 ..
 *	 1 + r = 5; r = 4
 *
 * Each r represents a smaller subset of this problem.  So for each r, we must
 * ask:  How many ways can you add one or more numbers less than or equal to r
 * to equal r?
 *
 * Keep answering this question recursively to yield an answer.  A possible
 * optimization is cache F(n, x) values in a multi dimensional array.
 *
 * Problem thread mentioned that Euler's generating functions are a super
 * efficient way of answering this problem, along with 78.  It's worth checking
 * out.
 */

int min(int m, int n) {
	if (m < n) {
		return m;
	}

	return n;
}

unsigned int sumEqualsNWithTermsLTEX(unsigned int n, unsigned int x) {
	unsigned int sum = 0;
	if (x <= 1) {
		return 1;
	}
	if (n <= 1) {
		return 1;
	}
	for (int z = x; z >= 1; z--) {
		int newN = n-z;
		int newX = min(z, newN);
		sum += sumEqualsNWithTermsLTEX(newN, newX);
	}
	return sum;
}

unsigned int answer(int n) {
	return sumEqualsNWithTermsLTEX(n, n-1);
}

int main() {
	std::cout << answer(100) << std::endl;
	return 0;
}
