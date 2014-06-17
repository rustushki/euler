#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector< std::vector<int> > generatePairs(int a) {

	static std::vector< std::vector< std::vector<int> > > cache(100);

	std::vector< std::vector<int> > pairs;
	if (cache[a].size() == 0) {


		if (a == 1) {
			return pairs;
		}

		for (int c = a-1; c >= ceil((double)a/2); c--) {
			std::vector<int> pair;
			pair.push_back(c);
			pair.push_back(a-c);

			pairs.push_back(pair);
		}

		cache[a] = pairs;

	} else {
		pairs = cache[a];
	}

	return pairs;
}

void printVec(std::vector<int> v) {

	for (int d=0; d < v.size(); d++) {
		std::cout << v[d] << ",";
	}
	std::cout << std::endl;
}


int main() {

	int n = 11;

	std::vector< std::vector<int> > currentSequences = generatePairs(n);
	int sum = currentSequences.size();
	bool firstTime = true;

	for (int s=0; s < currentSequences.size(); s++) {
		printVec(currentSequences[s]);
	}
	std::cout << currentSequences.size() << std::endl;

	while(currentSequences.size() != 1 || currentSequences[0].size() != n) {

		firstTime = false;

		std::vector< std::vector<int> > newSequences;

		for (int x = 0; x < currentSequences.size(); x++) {

			std::vector<int> thisSeq = currentSequences[x];

			std::vector<int> alreadyRemovedNums;

			for (int d = 0; d < thisSeq.size(); d++) {

				int numberToRemove = thisSeq[d];
				bool alreadyRemoved = false;
				for (int m = 0; m < alreadyRemovedNums.size(); m++) {
					if (alreadyRemovedNums[m] == numberToRemove) {
						alreadyRemoved = true;
						break;
					}
				}

				if (alreadyRemoved) {
					continue;
				}

				alreadyRemovedNums.push_back(numberToRemove);

				std::vector< std::vector<int> > pairs = generatePairs(numberToRemove);

				std::vector<int> removedSeq = thisSeq;

				// Remove element d
				removedSeq.erase(removedSeq.begin()+d);

				for (int p = 0; p < pairs.size(); p++) {

					std::vector<int> expandedSequence = removedSeq;

					std::vector<int> pair = pairs[p];
					expandedSequence.insert(expandedSequence.begin()+d, pair.begin(), pair.end());

					// sort expandedSequence
					sort(expandedSequence.begin(), expandedSequence.end());

					// look through newSequences to find any duplicates
					bool foundCopy = false;
					for (int n = 0; n < newSequences.size(); n++) {
						bool exactCopy = true;
						std::vector<int> testSeq = newSequences[n];
						for (int num = 0; num < testSeq.size(); num++) {
							if (testSeq[num] != expandedSequence[num]) {
								exactCopy = false;
								break;
							}
						}

						if (exactCopy) {
							foundCopy = true;
							break;
						}
					}

					// if duplicate not found add expandedSequence to newSequences
					if (!foundCopy) {
						newSequences.push_back(expandedSequence);
					}
				}
			}



		}


		sum += newSequences.size();
		currentSequences = newSequences;

		/*
		for (int s=0; s < newSequences.size(); s++) {
			printVec(newSequences[s]);
		}
		*/
		std::cout << newSequences.size() << std::endl;
		
	}


	std::cout << sum << std::endl;

	return 0;
}
