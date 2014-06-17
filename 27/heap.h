#include <cstring>
#include <vector>

class heap{

	public:
		std::vector<char*> heapdata;
		int size;
				
		heap(std::vector<char*> list);
		void heapify(int i);
		void build();
		int gt(int l, int r);
		void exchange(int x, int y);
		void insert();
		void root_delete();
		int left(int i);
		int right(int i);
		int parent(int i);
		void heapsort();

};
