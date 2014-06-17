#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

//    f
//      a   g
//    e   b
//  j  d c  h
//
//      i


unsigned long long getSolutionValue(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
	std::vector<int> extNodes;
	extNodes.push_back(f);
	extNodes.push_back(a);
	extNodes.push_back(b);
	extNodes.push_back(g);
	extNodes.push_back(b);
	extNodes.push_back(c);
	extNodes.push_back(h);
	extNodes.push_back(c);
	extNodes.push_back(d);
	extNodes.push_back(i);
	extNodes.push_back(d);
	extNodes.push_back(e);
	extNodes.push_back(j);
	extNodes.push_back(e);
	extNodes.push_back(a);

	int tenCount = 0;
	for (int x = 0; x < extNodes.size(); x++) {
		if (extNodes[x] == 10) {
			tenCount++;
			if (tenCount >= 2) {
				return 0;
			}
		}
	}

	// Find the minimum external node.
	int min = 11;
	int minOffset = 0;
	for (int x = 0; x < extNodes.size(); x += 3) {
		if (extNodes[x] < min) {
			min = extNodes[x];
			minOffset = x;
		}
	}

	unsigned long long value = 0;

	int place = 0;
	for (int x = minOffset-1; x >= 0; x--) {
		value += (unsigned long long) extNodes[x] * (unsigned long long) pow(10, place);
		place++;
		if (extNodes[x] == 10) {
			place++;
		}
	}

	for (int x = extNodes.size() - 1; x >= minOffset; x--) {
		value += (unsigned long long) extNodes[x] * (unsigned long long) pow(10, place);
		place++;
		if (extNodes[x] == 10) {
			place++;
		}
	}

	return value;
}

bool pushIfNotIn(std::vector<int> & usedDigits, int x) {
	if (std::find(usedDigits.begin(), usedDigits.end(), x) == usedDigits.end()) {
		usedDigits.push_back(x);
		return true;
	}

	return false;
}

int main() {
	unsigned long long biggestValue = 0;
	std::vector<int> usedDigits;
	for (int f = 1; f <= 10; f++) {
		usedDigits.push_back(f);
		for (int a = 1; a <= 10; a++) {
			if (!pushIfNotIn(usedDigits, a)) {
				continue;
			}

			for (int b = 1; b <= 10; b++) {
				if (!pushIfNotIn(usedDigits, b)) {
					continue;
				}

				// Compute Gon #1
				int gon1 = f + a + b;

				for (int c = 1; c <= 10; c++) {
					if (!pushIfNotIn(usedDigits, c)) {
						continue;
					}

					for (int g = 1; g <= 10; g++) {
						if (!pushIfNotIn(usedDigits, g)) {
							continue;
						}

						int gon2 = g + b + c;

						// Compute Gon #2
						if (gon1 != gon2) {
							usedDigits.pop_back();
							continue;
						}

						for (int d = 1; d <= 10; d++) {
							if (!pushIfNotIn(usedDigits, d)) {
								continue;
							}

							for (int h = 1; h <= 10; h++) {
								if (!pushIfNotIn(usedDigits, h)) {
									continue;
								}

								// Compute Gon #3
								int gon3 = d + c + h;

								if (gon1 != gon3) {
									usedDigits.pop_back();
									continue;
								}

								for (int e = 1; e <= 10; e++) {
									if (!pushIfNotIn(usedDigits, e)) {
										continue;
									}

									for (int i = 1; i <= 10; i++) {
										if (!pushIfNotIn(usedDigits, i)) {
											continue;
										}

										// Compute Gon #4
										int gon4 = e + d + i;

										if (gon1 != gon4) {
											usedDigits.pop_back();
											continue;
										}

										for (int j = 1; j <= 10; j++) {
											if (!pushIfNotIn(usedDigits, j)) {
												continue;
											}

											// Compute Gon #5
											int gon5 = j + e + a;

											if (gon1 != gon5) {
												usedDigits.pop_back();
												continue;
											}
											
											unsigned long long value = getSolutionValue(a, b, c, d, e, f, g, h, i, j);

											if (value > biggestValue) {
												biggestValue = value;
											}
											usedDigits.pop_back();
										}
										usedDigits.pop_back();
									}
									usedDigits.pop_back();
								}
								usedDigits.pop_back();
							}
							usedDigits.pop_back();
						}
						usedDigits.pop_back();
					}
					usedDigits.pop_back();
				}
				usedDigits.pop_back();
			}
			usedDigits.pop_back();
		}
		usedDigits.pop_back();
	}

	std::cout << biggestValue << std::endl;
	return 0;
}
