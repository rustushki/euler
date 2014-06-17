#include <iostream>

#define COEFF 8
#define AMOUNT 200

int denom[] = {
	  1
	, 2
	, 5
	, 10
	, 20
	, 50
	, 100
	, 200
};

int polynomial(int* coefficients) {
	
	int total = 0;
	for (int x = 0; x < COEFF; x++){
		total += denom[x] * coefficients[x];
		if (total > AMOUNT) {
			return -1;
		}
	}
	return total;
}

bool permutate(int* coefficients, int pivot, bool next_denom){
	if (pivot == COEFF){
		return false;
	}

	coefficients[pivot]++;
	if (coefficients[pivot] > AMOUNT/denom[pivot] || next_denom){
		coefficients[pivot] = 0;
		return permutate(coefficients, pivot+1, false);
	}
	return true;
}

int main(){
	int coefficients[COEFF] = {
		  0
		, 0
		, 0
		, 0
		, 0
		, 0
		, 0
		, 0
	};

	int combo = 0;

	int result;
	bool next_denom = false;
	while (permutate(coefficients, 0, next_denom)){
		result = polynomial(coefficients);
		if (result != -1) {
			if (result == AMOUNT){
				combo++;
				//std::cout << combo << std::endl;
			}
		}
		next_denom = (result == -1);
	}
	std::cout << combo << std::endl;
	return 0;
}
