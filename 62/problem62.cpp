#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

/* Problem 62
 *
 * Build a tree of digit nodes.  Each node in the tree represents a set of
 * numbers whose digits where sorted lead to the path to that node in the
 * tree--starting from the root to this particular node.
 *
 * The tree helps us quickly store and find counts of numbers which have the
 * same distribution of digits.
 */

struct DigitTreeNode {
	
	/// Initialize the node.
	DigitTreeNode() {
		this->count = 0;
		this->dig0 = NULL;
		this->dig1 = NULL;
		this->dig2 = NULL;
		this->dig3 = NULL;
		this->dig4 = NULL;
		this->dig5 = NULL;
		this->dig6 = NULL;
		this->dig7 = NULL;
		this->dig8 = NULL;
		this->dig9 = NULL;
		this->smallestCube = 0;
	}

	// Count of cubes which has the digits represented by the path through the
	// tree to this node.
	unsigned int count;

	// Children nodes
	DigitTreeNode* dig0;
	DigitTreeNode* dig1;
	DigitTreeNode* dig2;
	DigitTreeNode* dig3;
	DigitTreeNode* dig4;
	DigitTreeNode* dig5;
	DigitTreeNode* dig6;
	DigitTreeNode* dig7;
	DigitTreeNode* dig8;
	DigitTreeNode* dig9;

	// Smallest cube which has been found to have the digits represented by the
	// path through the tree to this node.
	unsigned long long smallestCube;
};

DigitTreeNode root;

/* check - Determine if the cube of x has a cube with a count of 'occurences'
 * permutations of the digits in the cube of x.  If so, return the smallest
 * cube which is a permatuation of the digits in the cube of x.
 *
 * Must run iteratively for all y below x from 1 to x-1.
 */
unsigned long long check(unsigned int x, unsigned int occurences) {
	unsigned long long cube = (unsigned long long )(x*x)*(unsigned long long)x;

	DigitTreeNode* p = &root;

	// Convert the x^3 into a string and sort it by its digits.
	std::ostringstream stream;
	stream << cube;
	std::string digits = stream.str();
	sort(digits.begin(), digits.end());

	// Find the node in the digit tree which correspondes to the cube of x.
	for (int x = 0; x < digits.size(); x++) {

		char smallest = digits[x];

		switch (smallest) {
			case '0':
				if (p->dig0 == NULL) {
					p->dig0 = new DigitTreeNode();
				}
				p = p->dig0;
				break;
			case '1':
				if (p->dig1 == NULL) {
					p->dig1 = new DigitTreeNode();
				}
				p = p->dig1;
				break;
			case '2':
				if (p->dig2 == NULL) {
					p->dig2 = new DigitTreeNode();
				}
				p = p->dig2;
				break;
			case '3':
				if (p->dig3 == NULL) {
					p->dig3 = new DigitTreeNode();
				}
				p = p->dig3;
				break;
			case '4':
				if (p->dig4 == NULL) {
					p->dig4 = new DigitTreeNode();
				}
				p = p->dig4;
				break;
			case '5':
				if (p->dig5 == NULL) {
					p->dig5 = new DigitTreeNode();
				}
				p = p->dig5;
				break;
			case '6':
				if (p->dig6 == NULL) {
					p->dig6 = new DigitTreeNode();
				}
				p = p->dig6;
				break;
			case '7':
				if (p->dig7 == NULL) {
					p->dig7 = new DigitTreeNode();
				}
				p = p->dig7;
				break;
			case '8':
				if (p->dig8 == NULL) {
					p->dig8 = new DigitTreeNode();
				}
				p = p->dig8;
				break;
			case '9':
				if (p->dig9 == NULL) {
					p->dig9 = new DigitTreeNode();
				}
				p = p->dig9;
				break;
			default:
				throw 1;
		}
	}

	// p is now the node in the Digit tree which correspondes to the cube of x.
	if (p != NULL) {

		// if we've not yet found cubes with this permutation, assume x is the
		// smallest.
		if (p->count == 0) {
			p->smallestCube = cube;
		}

		// Increment the count of permutions of these digits.
		p->count++;

		// If there have now been found the requested count of permutations,
		// return the smallest cube.
		if (p->count == occurences) {
			return p->smallestCube;
		}
	}

	// Otherwise return 0.
	return 0;
}

int main() {
	unsigned int x            = 0;
	unsigned int occurences   = 5;
	unsigned long long smallestCube = 0;

	for (x = 2; x < 10000; x++) {
		if ((smallestCube = check(x, occurences)) != 0) {
			break;
		}
	}

	std::cout << x << "*" << x << "*" << x << std::endl;
	std::cout << smallestCube << std::endl;
	return 0;
}
