#include <iostream>

// Exclusive upper and lower end of the range of fractions.
double rl = (double)1/(double)3;
double ru = (double)1/(double)2;


// Search for the upper most fraction with denominator == d which is less than
// the Upper Range (ru).
int upperEnd(int d) {
	// Numerators of the fractions to be tested.
	int l = 1;
	int h = d - 1;

	double den = d;

	double m = 0;
	while (h > l) {
		m = (int)(((h - l) / 2)+l);

		double t = m / den;

		if (t >= ru) {
			h = m - 1;
		} else if (t < ru) {
			l = m + 1;
		}
	}

	if ((double)h / (double)d < ru) {
		return h;
	}

	return h - 1;
}

// Search for the lower most fraction with denominator == d which is more than
// the Lower Range (rl).
int lowerEnd(int d) {

	// Numerators of the fractions to be tested.
	int l = 1;
	int h = d - 1;

	double den = d;

	double m = 0;
	while (h > l) {
		m = (int)(((h - l) / 2)+l);

		double t = m / den;

		if (t <= rl) {
			l = m + 1;
		} else if (t > rl) {
			h = m - 1;
		}
	}

	if ((double)l / (double)d > rl) {
		return l;
	}

	return l + 1;
}

// Find the Highest Common Factor.  This is the Binary GCD algorithm which was
// shamelessly taken straight from Wikipedia.  I'm far too lazy to actually
// write HCF (again).
unsigned int hcf(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return hcf(u >> 1, v);
        else // both u and v are even
            return hcf(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return hcf(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return hcf((u - v) >> 1, v);
 
    return hcf((v - u) >> 1, u);
}

int main() {

	long f = 0;

	// For all Denominators between 2 and 12000, inclusively...
	for (int d = 2; d <= 12000; d++) {

		// Find the numerators which yield fractions betwee 1/3 and 1/2.
		int l = lowerEnd(d);
		int u = upperEnd(d);

		// Check each of these fractions to confirm that they are wholly reduced.
		for (int n = l; n <= u; n++) {

			// If so, increment f.
			if (hcf(n,d) == 1) {
				//std::cout << "(" << n << "/" << d << ")" << std::endl;
				f++;
			}
		}
	}

	// Output result.
	std::cout << f << std::endl;

	return 0;
}
