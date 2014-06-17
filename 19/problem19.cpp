#include <iostream>

int days_of_month(int month, int year){
	int length[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && year % 4 == 0) {
		return 29;
	} else {
		return length[month-1];
	}
}

int main() {
	int year = 1901;
	int day_of_week = 3; // 0 - Sun, 1 - Mon, .. 6 - Sat
	int sundays = 0;

	while (year != 2001){
		for (int month = 1; month <= 12; month++) {
			day_of_week = (day_of_week + days_of_month(month, year)) % 7;
			if (day_of_week == 0) {
				sundays++;
			}
		}
		year++;
	}

	std::cout << sundays << std::endl;

	return 0;
}
