#include <cstring>
#include <vector>
#include <iostream>
#include "heap.h"

heap::heap(std::vector<char*> list) {
	this->heapdata = list;
}

void heap::heapify(int i){
	int l = this->left(i);
	int r = this->right(i);

	int largest;

	if (l <= this->size && this->gt(l, i)){
		largest = l;
	} else {
		largest = i;
	}

	if (r <= this->size && this->gt(r, largest)) {
		largest = r;
	}

	if (largest != i){
		this->exchange(i, largest);
		this->heapify(largest);
	}
}

void heap::build() {
	
	this->size = this->heapdata.size();
	for (int x = (int)(this->size/2); x > 0; x--){
		this->heapify(x);
	}
}

int heap::gt(int l, int r) {
	char* lw = (char*)this->heapdata[l-1];
	char* rw = (char*)this->heapdata[r-1];

	int x;
	for (x = 0; lw[x] != '\0' && rw[x] != '\0'; x++){
		if (lw[x] > rw[x]){
			return true;
		} else if (lw[x] < rw[x]) {
			return false;
		}
	}

	if (lw[x] == '\0'){
		return false;
	}

	return true;
}

void heap::exchange(int x, int y) {
	char temp[25];
	strcpy(temp, this->heapdata[x-1]);
	strcpy(this->heapdata[x-1], this->heapdata[y-1]);
	strcpy(this->heapdata[y-1], temp);
}

void heap::insert() {

}

void heap::root_delete() {
	this->heapdata[0];
}

int heap::left(int i){
	return 2*i;
}

int heap::right(int i){
	return 2*i+1;
}

int heap::parent(int i){
	return (int)i/2;
}

void heap::heapsort() {
	this->build();
	for (int i = this->size; i >= 2; i--){
		this->exchange(1, i);
		this->size--;
		this->heapify(1);
	}
}

