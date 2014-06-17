#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define WORDSIZE 16345

bool isTriangle(int n) {
   
   // If 8*n + 1 is a Perfect Square, then n must be a triangle number.
   int x = 1;
   for (x = 1; x*x <= (8*n + 1); x++);
   --x;

   return (x*x == (8*n+1));
}

int main() {

   // No need to do any fancy reading here.  words.txt is 16K, I'm OK with
   // reading it all in to a contiguous char array
   char words[WORDSIZE];
   FILE* fp = fopen("words.txt", "r");
   fread(words, 1, WORDSIZE, fp);
   fclose(fp);


   // Iterate over each character in the sequence.
   int count = 0;
   int wordSum = 0;
   for (int x = 0; x < WORDSIZE; x++) {

      // If the character is not meta, add the letter value to the word sum.
      if (words[x] != '"' && words[x] != ',') {
         wordSum += words[x] - 0x40;

      // When a meta character is found, check if the sum of the letter values
      // is a triange number.
      } else {

         // No need to check if 0 is a triangle number.
         if (wordSum != 0) {
            if (isTriangle(wordSum)) {
               count++;
            }
         }

         // Reset the sum of the letters since we're on a meta character.
         wordSum = 0;
      }
   }

   std::cout << "There are " << count << " triangle words in the English language.";

   return 0;
}
