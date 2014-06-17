#include <iostream>
#include <cmath>

#define DIGITS 10
int pandigital[DIGITS] {
	  0
	, 1
	, 2
	, 3
	, 4
	, 5
	, 6
	, 7
	, 8
	, 9
};

void output() {
	for (int x = 0; x < DIGITS; x++){
		std::cout << pandigital[x];
	}

	std::cout << std::endl;
	/*
	static int y = 15;
	if (y == 0) {
		exit(0);
	}
	y--;
	*/
}

bool num_exists_before_pos(int num, int pos) {
	for (int x = pos-1; x >=0; x--) {
		if (pandigital[x] == num) {
			return true;
		}
	}
	return false;
}

int permutate() {
	int x;
	bool next_found=false;
	for (x = DIGITS-2; x >= 0; x--) {
		while (pandigital[x]+1 <= DIGITS-1) {
			if (!num_exists_before_pos(++pandigital[x], x)){
				next_found = true;
				break;
			}
		}

		if (next_found) {
			break;
		} else if (x == 0) {
			return false;
		}
	}

	for (int y = x+1; y < DIGITS; y++){
		for (int consideration = 0; consideration < DIGITS; consideration++){
			if (!num_exists_before_pos(consideration, y)) {
				pandigital[y] = consideration;
				break;
			}
		}
	}
	//output();

	return true;
}

bool satisfies() {
	if ((pandigital[7]*100+pandigital[8]*10+pandigital[9]) % 17 != 0){
		return false;
	}
	if ((pandigital[6]*100+pandigital[7]*10+pandigital[8]) % 13 != 0){
		return false;
	}
	if ((pandigital[5]*100+pandigital[6]*10+pandigital[7]) % 11 != 0){
		return false;
	}
	if ((pandigital[4]*100+pandigital[5]*10+pandigital[6]) % 7 != 0){
		return false;
	}
	if ((pandigital[3]*100+pandigital[4]*10+pandigital[5]) % 5 != 0){
		return false;
	}
	if ((pandigital[2]*100+pandigital[3]*10+pandigital[4]) % 3 != 0){
		return false;
	}
	if ((pandigital[1]*100+pandigital[2]*10+pandigital[3]) % 2 != 0){
		return false;
	}
	return true;
}

int main(){
	int ans = 0;

	//output();
	do {
		if (satisfies()){
			output();
			ans++;
		}
	} while(permutate());

	std::cout << ans << std::endl;

	return 0;
}
