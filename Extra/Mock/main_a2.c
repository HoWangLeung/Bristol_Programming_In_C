/*
   Returns a copy of string s1 with all of the duplicate
   characters removed.
*/

#include "common.h"

char* strnodupes(const char* s);

int main(void)
{

   char* s2;

   s2 = strnodupes("Hello World!");
   assert(strcmp("Helo Wrd!", s2)==0);
   free(s2);
   s2 = strnodupes("a-aaaaaAAAAAAAAaaaaaaaa");
   assert(strcmp("a-A", s2)==0);
   free(s2);
   s2 = strnodupes("HHiHHiiidiHiHiedHidiHi");
   assert(strcmp("Hide", s2)==0);
   free(s2);
   s2 = strnodupes("Subdermatoglyphic");
   assert(strcmp("Subdermatoglyphic", s2)==0);
   free(s2);

   return 0;
}
