#include <stdio.h>

int fact(int a);

int main(void)
{

   int a, f;

   printf("Input a number :\n");
   scanf("%d", &a);
   f = fact(a);
   printf("%d! is %d\n", a, f);
   return(0);

}

int fact(int a)
{

   if(a > 0)
      return ( a * fact(a - 1) );
   else
      return 1;

}
