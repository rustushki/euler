#include <string.h>
#include <iostream>
#include <gmp.h>

void reverse(char* forward) {
	int last = strlen(forward)-1;

	char* reverse = new char[last+3];
	for (int n = last; n >= 0; n--){
		reverse[last-n] = forward[n];
	}
	strcpy(forward, reverse);
	delete [] reverse;
}

bool is_palindrome(char* str) {
	int last = strlen(str)-1;
	for (int n = 0, m = last; n <= last; n++, m--){
		if (str[n] != str[m]){
			return false;
		}
	}
	return true;
}

bool lychrel(mpz_t* a, int depth) {

	// Determine reverse of a
	char*rev = mpz_get_str(NULL, 10, *a);
	reverse(rev);
	
	// Init b as reverse of a
	mpz_t b;
	mpz_init(b);
	mpz_set_str(b, rev, 10);

	// Add a and b
	mpz_add(*a, *a, b);

	// is result a palindrome?  if not resursively check result
	char*result = mpz_get_str(NULL, 10, *a);
	if (is_palindrome(result)) {
		return true;
	} else if (depth < 50) {
		//std::cout << result << std::endl;
		return lychrel(a, depth+1);
	}
	return false;
}

int main() {
	mpz_t a;
	mpz_init(a);
	int ans = 0;
	for (int n = 0; n < 10000; n++) {
		mpz_set_ui(a, n);
		if (lychrel(&a, 1)){
			ans++;
		}
		//std::cout << std::endl;
	}
	std::cout << 10000-ans << std::endl;
	return 0;
}
