#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

std::vector<unsigned long> base;
std::vector<unsigned long> expt;

long double biggest = 0;
int biggestLineNumber = 0;

/* -----------------------------------------------------------------------------
 * explode - Utility function.  Given a string, break it up into a vector of
 * substrings by delimeter.  Nothing special here.
 */
std::vector<std::string> explode(std::string str, std::string delimeter) {
	std::vector<std::string> result;

	int newPos = 0;
	int oldPos = 0;

	str += delimeter;

	while ((newPos = str.find(delimeter, oldPos)) != std::string::npos) {
		std::string substr = str.substr(oldPos, newPos-oldPos);
		result.push_back(substr);
		oldPos = newPos+delimeter.size();
	}

	return result;
}

/* -----------------------------------------------------------------------------
 * readNumbers - Read the base/exponent pairs.  No special sauce here.
 */
void readNumbers() {

	// Input file.
	std::ifstream fin("base_exp.txt");

	while (!fin.eof()) {

		char line[50];

		fin.getline(line, 50);

		std::string strLine(line);

		std::vector<std::string> pair = explode(strLine, ",");

		base.push_back(atoi(pair[0].c_str()));
		expt.push_back(atoi(pair[1].c_str()));
	}
}

/* -----------------------------------------------------------------------------
 * logExp - Given a base (a) and an exponent (b), determine the logarithmic
 * plot of the value of a^b.  Return the result.
 *
 * More precisely, log(a^b) == b*log(a)
 */
long double logExp(unsigned int base, unsigned int exp) {
	long double baseLg = log10((long double)base);
	long double val = exp*baseLg;
	return val;
}

int main() {

	// Read in the bases and exponents from the problem file.
	// bases go into the 'base' vector.
	// exponents go into the 'expt' vector.
	readNumbers();

	// Iterate over each pair.
	for (int x = 0; x < base.size(); x++) {
		
		// Determine the log10() of value of the exponent/base pair.
		long double check = logExp(base[x], expt[x]);

		// Is it bigger than the biggest so far?
		if (check > biggest) {
			
			// Save that result and line number.
			biggest = check;
			biggestLineNumber =  x+1;

		}

	}

	// Output the line number of the largest pair.
	std::cout << biggestLineNumber << std::endl;

	return 0;
}
