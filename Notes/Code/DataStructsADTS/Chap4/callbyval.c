#include <stdio.h>

void fnc1(int a);

int main(void)
{

   int x = 1;

   fnc1(x);
   printf("%d\n", x);

}

void fnc1(int a)
{
   a = a + 1;
}
