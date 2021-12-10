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

   dict* d = dict_init(50);
   assert(dict_add(d, "one"));
   assert(dict_add(d, "one"));
   assert(dict_add(d, "two"));

   assert(dict_spelling(d, "one"));
   assert(dict_spelling(d, "two"));
   assert(!dict_spelling(d, "Two"));
   assert(!dict_spelling(d, "One"));

   dict_free(d);
   return EXIT_SUCCESS;
}
