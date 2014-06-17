#include <iostream>
#include <vector>

int main() {

   // This is the product of D1, D10, D100 ... D100000
   int product = 1;

   // r is the current number to be concatenated to the irrational number D.
   int r = 1;

   // p is the position in the sequence.
   int p = 1;

   // n is the position we're looking for.
   int n = 1;

   while (n <= 100000) {
      // Push all digits of r onto a stack.
      int q = r;
      std::vector<int> stack;
      while (q >= 1) {
         stack.push_back(q % 10);
         q /= 10;
      }

      // Pop each element off the stack.
      while (stack.size() > 0) {

         // If the position is the same as the one we're looking for...
         if (p == n) {

            // Multiply to the product
            product *= stack.back();

            // Raise n to the next order of magnitude.
            n *= 10;
         }

         // Remove from the top of the stack.
         stack.pop_back();

         // Count the position of the element.
         p++;
      }

      r++;
   }

   std::cout << "Product: " << product << std::endl;


   

   return 0;
}
