#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Shorthand for talking about Cards.
typedef std::string CARD;

// Shorthand for talking about Hands.
typedef std::vector<CARD> HAND;

// Shorthand for talking about distribution of like-valued cards.
typedef std::vector<unsigned int> CARDDIST;


// Store all hands read from poker.txt here.
std::vector<HAND> p1Hands;
std::vector<HAND> p2Hands;

// Card Values to be used throughout the program.
enum CardValue {
	  CARDVALUE_2
	, CARDVALUE_3
	, CARDVALUE_4
	, CARDVALUE_5
	, CARDVALUE_6
	, CARDVALUE_7
	, CARDVALUE_8
	, CARDVALUE_9
	, CARDVALUE_T
	, CARDVALUE_J
	, CARDVALUE_Q
	, CARDVALUE_K
	, CARDVALUE_A
	, CARDVALUE_COUNT
};

// Hand Types which re discovered and compared throughout the program.
enum HandType {
	  HANDTYPE_HIGHCARD
	, HANDTYPE_ONEPAIR
	, HANDTYPE_TWOPAIR
	, HANDTYPE_THREEOFAKIND
	, HANDTYPE_STRAIGHT
	, HANDTYPE_FLUSH
	, HANDTYPE_FULLHOUSE
	, HANDTYPE_FOUROFAKIND
	, HANDTYPE_STRAIGHTFLUSH
	, HANDTYPE_ROYALFLUSH
};

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
 * getCardValue - 
 */
CardValue getCardValue(CARD card) {
	char val = card[0];
	switch(val) {
		case '2':
			return CARDVALUE_2;
		case '3':
			return CARDVALUE_3;
		case '4':
			return CARDVALUE_4;
		case '5':
			return CARDVALUE_5;
		case '6':
			return CARDVALUE_6;
		case '7':
			return CARDVALUE_7;
		case '8':
			return CARDVALUE_8;
		case '9':
			return CARDVALUE_9;
		case 'T':
			return CARDVALUE_T;
		case 'J':
			return CARDVALUE_J;
		case 'Q':
			return CARDVALUE_Q;
		case 'K':
			return CARDVALUE_K;
		case 'A':
			return CARDVALUE_A;
	}
}

/* -----------------------------------------------------------------------------
 * getCardDist - given a hand, determine the number of occurrences of each card
 * value and return a Card Distribution.
 */
CARDDIST getCardDist(HAND hand) {

	CARDDIST dist(CARDVALUE_COUNT, 0);

	for (int x = 0; x < 5; x++) {
		CardValue cv = getCardValue(hand[x]);
		dist[cv]++;
	}

	return dist;

}

/* ------------------------------------------------------------------------------
 * allSameSuit - Returns true if all cards in the hand are of the same suit.
 * Nothing Magic or Special here.
 */
bool allSameSuit(HAND hand) {
	char suit;

	for (int cardPos = 0; cardPos < hand.size(); cardPos++) {
		char thisSuit = hand[cardPos][1];

		if (cardPos == 0) {
			suit = thisSuit;
		} else if (suit != thisSuit) {
			return false;
		}
	}
	return true;
}

/* ------------------------------------------------------------------------------
 * isAllHighCards - Given a Hand, determine whether the Cards are in order.
 * Note that Aces may be played LOW (value == 1) or HIGH (value == 13), but
 * sequentiality does not wrap around.
 *
 * TODO: this function probably doesn't handle HIGH Aces, but I'm not 100%
 * sure.
 */
bool isSequential(HAND hand) {
	
	// Build a vector of boolean slots.  If the slot is filled by a card, it's
	// marked true.  Otherwise, it's false.
	std::vector<bool> pos(CARDVALUE_COUNT+1, false);

	// Go through each card and park each position in our boolean slots.
	for (int cardPos = 0; cardPos < hand.size(); cardPos++) {
		CardValue cv = getCardValue(hand[cardPos]);
		pos[cv+1] = true;

		// Special Case:
		// Ace may be played LOW or HIGH.  So mark it in both slots.
		if (cv == CARDVALUE_A) {
			pos[0] = true;
		}
	}


	// Now iterate over each slot.
	bool foundFirstCard = false;
	bool isLowAce = false;
	unsigned int sequenceCount = 0;
	for (int slot = 0; slot <= CARDVALUE_COUNT+1; slot++) {

		// Has the slot been filled?
		bool slotFilled = pos[slot];

		// If the first filled slot has not yet been found,
		if (!foundFirstCard) {

			// And this slot is filled,
			if (slotFilled) {

				// Now we've found the first card.
				foundFirstCard = true;

				// Special Case: If the slot is position 0, we're seeking to
				// play the ace LOW.
				if (slot == 0) {
					isLowAce = true;
				}

				// Increment the sequence count.
				sequenceCount++;
			}

		// If the first card has already been found,
		} else if (slotFilled) {

			// Increment the sequence count.
			sequenceCount++;

			// If the sequence count is now 5, that means the hand is
			// considered sequential.
			if (sequenceCount == 5) {
				break;
			}

		// If the slot is not filled,
		} else if (!slotFilled) {

			// Reset the sequence count.
			sequenceCount = 0;

			// Special Case:
			// Ace may be played LOW or HIGH.
			if (isLowAce) {
				foundFirstCard = false;
				isLowAce = false;
				continue;
			}

		}
	}

	// Sequence Count of 5 is considered sequential.
	if (sequenceCount == 5) {
		return true;
	}

	// Anything else is not.
	return false;
}


/* ------------------------------------------------------------------------------
 * isAllHighCards - Given a Hand, determine whether the Cards are Ten, Jack,
 * Queen, King and Ace.
 */
bool isAllHighCards(HAND hand) {
	bool aFound = false;
	bool kFound = false;
	bool qFound = false;
	bool jFound = false;
	bool tFound = false;
	for(int x = 0; x < 5; x++) {
		CardValue cv = getCardValue(hand[x]);
		if (cv == CARDVALUE_A) {
			aFound = true;
		}
		if (cv == CARDVALUE_K) {
			kFound = true;
		}
		if (cv == CARDVALUE_Q) {
			qFound = true;
		}
		if (cv == CARDVALUE_J) {
			jFound = true;
		}
		if (cv == CARDVALUE_T) {
			tFound = true;
		}
	}

	return (aFound && kFound && qFound && jFound && tFound);
}

/* ------------------------------------------------------------------------------
 * getMatchesType - Given a hand which is not a FLUSH, ROYAL FLUSH, STRAIGHT
 * FLUSH or STRAIGHT, determine it's hand type.  This is all quite readable.
 */
HandType getMatchesType(HAND hand) {
	CARDDIST cardDist = getCardDist(hand);

	HandType type = HANDTYPE_HIGHCARD;
	for (int x = 0; x < CARDVALUE_COUNT; x++) {
		if (cardDist[x] == 2) {
			if (type == HANDTYPE_ONEPAIR) {
				return HANDTYPE_TWOPAIR;
			} else if (type == HANDTYPE_THREEOFAKIND) {
				return HANDTYPE_FULLHOUSE;
			} else {
				type = HANDTYPE_ONEPAIR;
			}
		} else if (cardDist[x] == 3) {
			if (type == HANDTYPE_ONEPAIR) {
				return HANDTYPE_FULLHOUSE;
			} else {
				type = HANDTYPE_THREEOFAKIND;
			}
		} else if (cardDist[x] == 4) {
			return HANDTYPE_FOUROFAKIND;
		}
	}

	return type;
}

/* ------------------------------------------------------------------------------
 * getHandType - Determine the type of hand.  This code is pretty readable and
 * most of the magic happens in help functions.
 *
 */
HandType getHandType(HAND hand) {

	if (allSameSuit(hand)) {
		if (isSequential(hand)) {
			if (isAllHighCards(hand)) {
				return HANDTYPE_ROYALFLUSH;
			} else {
				return HANDTYPE_STRAIGHTFLUSH;
			}
		} else {
			return HANDTYPE_FLUSH;
		}
	} else if (isSequential(hand)) {
		return HANDTYPE_STRAIGHT;
	} else {
		return getMatchesType(hand);
	}

	return (HandType)0;
}

/* ------------------------------------------------------------------------------
 * compareMatches - Given two hands which have been determined to not have a
 * STRAIGHT, FLUSH, ROYAL FLUSH or STRAIGHT FLUSH, but that are of the same
 * hand type, determine which hand wins.
 *
 * Do not attempt to use this function if the two hand types do not match!  I'd
 * add an assertion to this end, but that would decrease efficiency.
 *
 * Return 1 if p1 wins, -1 if p2 wins and 0 if uncertain.
 * 
 */
int compareMatches(HAND p1, HAND p2) {

	CARDDIST distP1 = getCardDist(p1);
	CARDDIST distP2 = getCardDist(p2);

	// Find the highest like match.

	// Search for Match Types: Four of a Kind, Three of a Kind, Two of a Kind
	// and finally Highest Card--in that order.  Search for each of these
	// starting with the highest valued cards.
	//
	// Using this approach, the first match type discovered which the other
	// hand does not have, must be the winning hand.  Otherwise, search for the
	// next match type.
	for (int matchCount = 4; matchCount >= 1; matchCount--) {

		for (int x = CARDVALUE_COUNT - 1; x >= 0; x--) {

			// Does P1 and P2 have the Match Type?  If so, move to the next
			// match type.
			if (distP2[x] == matchCount && distP1[x] == distP2[x]) {
				break;

			// If only P1 has the match type, P1 wins.
			} else if (distP1[x] == matchCount) {
				return 1;

			// If only P2 has the match type, P2 wins.
			} else if (distP2[x] == matchCount) {
				return -1;
			}
		}
	}

	return 0;
}

/* ------------------------------------------------------------------------------
 * compareHands - Return 1 if p1 wins, -1 if p2 wins and 0 if uncertain.
 * Should never return 0.
 */
int compareHands(HAND p1, HAND p2) {

	// Determine the hand type for each hand.
	HandType p1ht = getHandType(p1);
	HandType p2ht = getHandType(p2);

	// Case #1: If the hand types are different, the better hand type always
	// wins.  In this case Player 1 wins.
	if (p1ht > p2ht) {

		return 1;

	// Case #3:  The hand types match.  Read compareMatches for further details
	// in this elegant approach.
	} else if (p1ht == p2ht) {

		return compareMatches(p1, p2);

	// Case #3: If the hand types are different, the better hand type always
	// wins.  In this case Player 2 wins.
	} else {
		return -1;
	}
}

/* ------------------------------------------------------------------------------
 * readHands - Read the hands from the input file 'poker.txt'.  Nothing magical
 * happening here.  The hands are read into p1Hands and p2Hands--which are
 * assumed globals.
 *
 * Assume UNIX style line endings for simplicity.
 */
void readHands() {
	
	// Input file.
	std::ifstream fin("poker.txt");

	// Read until the end of file.
	while (!fin.eof()) {

		// Storage.
		char hand[15];
		std::string shand;
		HAND phand;

		// Read and Store Hand 1
		fin.read(hand, 15);
		shand = std::string(hand).erase(14);
		phand = explode(shand, " ");
		p1Hands.push_back(phand);

		// Read and Store Hand 2
		fin.read(hand, 15);
		shand = std::string(hand).erase(14);
		phand = explode(shand, " ");
		p2Hands.push_back(phand);
	}

}

int main() {

	readHands();

	int p1wins = 0;
	int unknown = 0;

	for (int x = 0; x < 1000; x++) {

		int result = compareHands(p1Hands[x], p2Hands[x]);

		if (result == 1) {
			p1wins++;
		} else if (result == 0) {
			unknown++;
		}
	}

	std::cout << "P1 wins: " << p1wins  << std::endl;
	std::cout << "Unknown: " << unknown << std::endl;

	return 0;
}
