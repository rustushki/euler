#include <iostream>

int factorial(int n) {
   if (n == 0) {
      return 1;
   }

   return n*factorial(n-1);
}

bool isProblem34(int n) {
   int sum = 0;
   int r = n;
   while (r >= 1) {
      if (sum > n) {
         break;
      }

      sum += factorial(r % 10);
      r /= 10;
   }

   return (sum == n);
}

int main() {
   int sum = 0;
   for (int n = 10; n < 1000000-1; n++) {
      if (isProblem34(n)) {
         sum += n;
      }
   }

   std::cout << "Answer: " << sum << std::endl;
   return 0;
}
