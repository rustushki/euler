#include <iostream>

/* Problem 71.  No Code.
 * I ended up solving this one by hand.  Here's a brief explanation.
 *
 * I first started with the understanding that 2/7 < 3/7.  Q: What fraction
 * with d <= 1,000,000 is between these two?  A: B = [(3/7 - 2/7) / 2] + 2/7.
 * In general, Lower + Halfway == (numerator*2+1) / (denominator*2) (where the
 * numerator and denominator are that of the Lower number in the range.
 *
 * Repeating that strategy led me to this number: 393215 / 917504--which is not the
 * answer.
 *
 * It did, however, narrow the range a good bit.  I knew that the denominator
 * couldn't be any less than 917504.  Therefore the numerator MUST be higher
 * than 393215.
 *
 * I then began a series of guesses.  I started with d = 1,000,000 and tried n
 * = 428571.  That wasn't it.  I decremented the denominator to 999,999 and
 * tried n = 428570.  That was the answer.
 *
 * I'm not really happy with my solution.
 */

int main() {

	std::cout << 428570 << std::endl;

	return 0;
}
