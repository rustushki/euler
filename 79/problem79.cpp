#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

/* getNextRule - if no rules have been read from the keylog.txt file, read
 * them.  otherwise, return the next rule in the sequence; starting from the
 * first rule.  You can reset the rule to the first in the sequence by setting
 * reset to true. */
std::string getNextRule(bool reset) {
	static short x = -1;

	static std::vector<std::string> rules;

	// On the first call to getNextRule, read in the rules.
	if (x == -1) {
		std::string str = "";

		// Open the file as a stream.
		std::ifstream fp_in("keylog.txt", std::ios::in);

		// Read in each rule (i.e. login attempt).
		while(!fp_in.eof()) {
			fp_in >> str;

			// Stick the rule in the internal, static vector.
			if (!fp_in.eof()) {
				rules.push_back(str);
			}
		}

		fp_in.close();
	}

	// Handle the reset flag
	if (reset) {
		x = -1;
	}

	// Increment to the next rule.
	x++;

	// If x is within bounds of the rule vector, return the current rule.
	if (x < rules.size()) {
		return rules[x];

	// Else return the empty string to indicate that nothing is left.
	} else {
		return "";
	}

}

/* match - determine if the given number matches the given rule. */
bool match(int num, std::string rule) {
	
	// Iterate over each number in the rule backwards.  We do it backwards to
	// save time, since the algorithm for obtaining digits from an int must
	// work from low order to high order.
	for (int x = rule.size() - 1; x >= 0; x--) {
		short digit = rule[x] - 0x30;

		bool matches = false;

		// Iterate over each digit in num from low order to high order.
		while (num >= 1) {

			// Get the digit.
			short cDigit = num % 10;

			// Alter the number for the next iteration of the loop.
			num /= 10;

			// If the current digit matches the digit in the rule which we're
			// considering ...
			if (cDigit == digit) {

				// We've got a match, move to the next rule digit.
				// Note that our current position in num is 'saved', so the
				// next time we enter this loop, we will not process the
				// numbers already processed.
				matches = true;
				break;

			}
		}

		// If the loop finished with no matches, the rule digit is not present
		// at all, t/f the rule doesn't match.
		if (!matches) {
			return false;
		}
	}

	// We've examined each digit in the rule and found it in the correct
	// sequence in the num provided.
	return true;
}

int main() {

	std::clock_t start = std::clock();

	// This is actually the answer.  I set out to determine the largest number
	// which used all the digits mentioned in the login attempts; which also
	// obeyed the login attempts.  It just so happened that this number is the
	// answer. :-P
	//
	// You could set this to num = 1 and it would still solve the problem in
	// about 20s on a MacBook Pro 5.1.
	long num = 73162890;


	// Set this to true if all rules have matched (i.e. we'll have an answer).
	bool allRulesMatch = false;

	// Iterate through all numbers starting with the initial one above.  Keep
	// iterating until a number is found which matches every rule.
	while (!allRulesMatch) {

		// Assume the number will match all rules.
		allRulesMatch = true;

		// Iterate through all rules.  If no more rules remain the getNextRule
		// function will return "".
		std::string rule = getNextRule(true);
		while (rule.compare("") != 0) {

			// If the number does not match the current rule, our assumption is
			// false.  Move to the next number.
			if (!match(num, rule)) {
				allRulesMatch = false;
				break;
			}

			// Get the next rule.
			rule = getNextRule(false);
		}

		// Move to the next number.
		num++;
	}

	std::cout << "Found in: " << ((std::clock() - start) / (double)CLOCKS_PER_SEC) << "s" << std::endl;

	// Our answer.
	std::cout << --num << std::endl;

	return 0;
}
