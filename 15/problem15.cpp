#include <gmp.h>
#include <iostream>
#include <vector>
int H = 21, W = 21;
mpz_t ans;

struct pair {
	int x;
	int y;
	mpz_t result;
};

std::vector <struct pair*> pairs;

void store(int x, int y, mpz_t result) {
	struct pair *p =  new struct pair();
	p->x = x;
	p->y = y;
	mpz_set(p->result, result);
	pairs.push_back(p);
}

void lookup(int x, int y, mpz_t& result){
	mpz_init(result);
	for (int cx = 0; cx < pairs.size(); cx++) {
		if ((pairs[cx]->x == x && pairs[cx]->y == y) || (pairs[cx]->x == y && pairs[cx]->y == x)) {
			mpz_set(result, pairs[cx]->result);
		}
	}
}

void trace(int x, int y) {
	mpz_t result;
	lookup(x ,y, result);
	if (mpz_cmp_si(result, 0) != 0){
		mpz_add(ans, ans, result);
	} else {
		//std::cout << x << "," << y << std::endl;
		if (x < W && y < H) {
			trace(x+1, y);
			trace(x, y+1);
		} else if (x == W && y < H) {
			trace(x, y+1);
		} else if (y == H && x < W) {
			trace(x+1, y);
		} else if (x == H && y == W) {
			mpz_add_ui(ans, ans, 1);
		}
	}
}

int main() {
	for (int x = 20; x >= 1; x--) {
		for (int y = 20; y >= 1; y--) {
			if (x == y) {
				gmp_printf("%d: %Zd\n", x, ans);
			}
			mpz_init(ans);
			trace(x,y);
			store(x, y, ans);
		}
	}
	gmp_printf("%Zd\n", ans);
	return 0;
}
