/* 
   Return the count of numbers in the array l (of size n)
   which are unique (i.e. duplicates are not counted)
*/

#include "common.h"

int numdiff(const int l[], const int n);

int main(void)
{
   int l[] = {100484783, 2, 30, -999999999, 3, 222222, -89492981, 1, 456889009};
   int m[] = {-567, 4, 99999, 0, 4, 4};
  // assert(numdiff(l, 9) == 9);
    assert(numdiff(m, 6) == 4);
   // assert(numdiff(m, 5) == 4);
   // assert(numdiff(m, 3) == 3);
   // assert(numdiff(NULL, 0) == 0);
   return 0;
}
