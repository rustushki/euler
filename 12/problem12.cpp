#include <iostream>

int count_factors(int number) {
	if (number > 3) {
		int num_factors = 0;
		int top = number;
		for (int x = 1; x <= top; x++) {
			if (number % x == 0){
				top = number / x;
				num_factors++;
				if (x * x != number){
					num_factors++;
				}
			}
		}
		return num_factors;
	} else if (number > 1){
		return 2;
	}
	return 1;
}

int main(){
	int x = 1;
	int triangle_num = 1;
	while (count_factors(triangle_num) < 500) {
		x++;
		triangle_num += x;
	}
	
	std::cout << triangle_num;

	return 0;
}
