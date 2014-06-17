#include <iostream>

/* choose - semantically, this is correct, but it overflows.  Fortunately, we
 * only need to know the earliest k for n which causes n choose k > 1000000.
 * Consequently, for that x <= k and x >= n - k, this function does not
 * overflow!
 */
int choose(int n, int k) {
	
	// Choose(n, k) = (n!)/(k!*(n-k)!)
	// Equivalent to ...
	// 
	// Say n = 5, k =3
	// 5!     = 1*2*3*4*5
	// 3!     = 1*2*3
	// (5-3)! = 1*2
	// t/f: 
	// (1*2*3*4*5)/((1*2*3)*(1*2)) = (4*5)/(1*2)
	//
	// q's multipliers are bounded by k+1 and n.
	// q's divisors are bounded by 1 and k.
	// You can then compute q in linear growth

	unsigned long long q = 1;
	for (int x = k+1; x <= n; x++) {
		q *= x;
		q /= x-k;
	}

	return q;
}

int main() {

	int values = 0;

	// We know that 23 choose 10 is the smallest n and k where n choose k is
	// greater than 1000000
	for (int n = 23; n <= 100; n++) {

		// Only need to check up to halfway
		for (int k = 1; k <= n/2; k++) {

			// It'll overflow, but we don't care!
			int comb = choose(n, k);

			if (comb > 1000000) {

				// As soon as you hit the first k for n where n choose k is
				// greater than 1000000, go to next n.  We may determine the
				// number of k's which satisfy the condition based on the below
				// formula.
				values += (n - (k*2)+1);
				break;
			}
		}
	}

	std::cout << "Count of values of n choose k > 1000000, where 1 <= n <= 100 := " << values << std::endl;

	return 0;
}
