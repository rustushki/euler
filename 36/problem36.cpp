#include <iostream>
#include <vector>

bool isPalindromic(int a, int base) {
   std::vector<int> digit;
   while (a >= 1) {
      digit.push_back(a % base);
      a /= base;
   }

   int ho = 0;
   int lo = digit.size()-1;

   bool isPalindromic = false;
   while (digit[ho] == digit[lo]) {
      if (ho >= lo) {
         isPalindromic = true;
         break;
      }
      ++ho;
      --lo;
   }

   return isPalindromic;
}

int main() {
   int sum = 0;
   for (int x = 1; x <= 1000000; x++) {

      // No need to check even numbers since no even numbers are palindromic in
      // binary.
      if (x % 2 != 0) {
         if (isPalindromic(x,10) && isPalindromic(x,2)) {
            sum += x;
         }
      }
   }
   std::cout << "Answer: " << sum << std::endl;
   return 0;
}
