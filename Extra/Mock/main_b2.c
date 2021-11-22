/*
   Return which number in the array l (of size n) is numerically closest
   to the average (mean) of all the numbers. In the case of a tie (i.e.
   1 or more of them are equally distant from the average) then the first
   such number in the list is returned.
*/

#include "common.h"

int closestmean(const int l[], const int n);

int main(void)
{
   int l[] = {10, 20, 30, 40};
   int m[] = {-5, 0, 10, -10, 5};
   int r[] = {10000000, 20000000, 0, -50000000};
   int t[] = {-5, 5};
   assert(closestmean(l, 4)==20);
   assert(closestmean(m, 5)==0);
   assert(closestmean(l, 1)==10);
   assert(closestmean(r, 4)==0);
   assert(closestmean(t, 2)==-5);
   assert(closestmean(&l[1], 3)==30);
   return 0;
}
