#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include "heap.h"

#define BUFF_SIZE 1024

std::vector<char*> read() {
	FILE* f = fopen("/home/rustushki/Source/euler/22/names.txt", "r");
	char data[BUFF_SIZE] = "";
	std::vector<char*> name_vec;


	char name[25];

	// Read a chunk
	int x = 0;
	int name_i = 0;
	int read = BUFF_SIZE;
	while (!feof(f) || x < read-1) {
		if (strlen(data) == 0 || x >= read){
			if (!feof(f)) {
				read = fread(data, 1, BUFF_SIZE, f);
				if (read < BUFF_SIZE){
					int bla =0;
				}
			} else {
				break;
			}
			x = 0;
		}
		while (data[x] != ',' && x < read) {
			if (data[x] != '"' && data[x] != ',') {
				name[name_i] = data[x];
				name_i++;
			}

			// Next Char in Buffer
			x++;
		}


		if (data[x] == ',' || (x == read && feof(f))) {
			// End Name String.
			name[name_i] = 0;

			// Put the Name in the List
			char* new_name = new char[25];
			strcpy(new_name, name);
			name_vec.push_back(new_name);

			// Start New Name
			name_i = 0;

			// Next Char in Buffer
			x++;
		}
	}
	fclose(f);
	return name_vec;
}

int score(char* name){
	static int position = 1;
	int score = 0;
	for (int x = 0; x < strlen(name); x++){
		score += name[x] - 64;
		if (position == 938) {
			int bla =0;
		}
	}
	return position++ * score;
}

int main() {
	std::vector<char*> name_vec = read();

	heap h(name_vec);
	h.heapsort();
	name_vec = h.heapdata;

	int total = 0;
	for (int x = 0; x < name_vec.size(); x++) {
		std::cout << name_vec[x] << std::endl;
		total += score((char*)name_vec[x]);
	}

	std::cout << total;

	return 0;
}
