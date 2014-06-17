#include <iostream>
#include <vector>
#include <cmath>

bool isPrime(int n) {
   if (n == 2) {
      return true;
   }

   for (int x = 2; x*x <= n; x++) {
      if (n % x == 0) {
         return false;
      }
   }
   
   return true;
}

bool isCircularPrime(int n) {
   if (!isPrime(n)) {
      return false;
   }

   std::vector<int> digit;

   int r = n;
   while (r >= 1) {
      digit.push_back(r % 10);
      r /= 10;
   }

   int shiftCt = 0;
   while(shiftCt <= digit.size()-1) {

      digit.insert(digit.begin(), digit.back());
      digit.pop_back();
      shiftCt++;

      int n = 0;
      for (int x = digit.size() - 1; x >= 0; x--) {
         n += digit[x] * pow(10, x);
      }

      if (!isPrime(n)) {
         return false;
      }
   }

   return true;
}

int main() {

   int count = 0;
   for (int x = 2; x <= 1000000; x++) {
      if (isCircularPrime(x)) {
         count++;
      }
   }

   std::cout << "Circular Prime Count Beneath 1000000: " << count << std::endl;


   return 0;
}
