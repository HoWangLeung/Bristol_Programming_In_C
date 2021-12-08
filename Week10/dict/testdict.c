/*
Trivial testing file for Dictionary; notice it is case-sensitive.
Should work for the any Dictionary implementation
*/
#include "dict.h"

#define BIGSTR 1000

int main(void)
{
   assert(!dict_add(NULL, ""));
   assert(!dict_add(NULL, "one"));
   assert(!dict_spelling(NULL, ""));
   assert(!dict_spelling(NULL, "one"));

   dict *d = dict_init(50);

   assert(dict_add(d, "one"));
   assert(dict_add(d, "one"));
   assert(dict_add(d, "one"));

   assert(dict_add(d, "aga"));
   assert(dict_add(d, "abcde"));
   assert(dict_add(d, "Abcde"));
   assert(dict_add(d, "Abcde."));

   assert(dict_add(d, "one"));
   assert(dict_add(d, "two"));
   assert(dict_add(d, "christmas"));
   assert(dict_add(d, "However"));

   assert(dict_spelling(d, "one"));
   assert(dict_spelling(d, "two"));
   assert(!dict_spelling(d, "Two"));
   assert(!dict_spelling(d, "One"));

   assert(dict_spelling(d, "aga"));
   assert(dict_spelling(d, "abcde"));
   assert(dict_spelling(d, "Abcde"));
   assert(dict_spelling(d, "Abcde."));
   //print(d);
   //mysprinter(d);
   dict_free(d);
   printf("END OF TESTING !\n");

   return EXIT_SUCCESS;
}
