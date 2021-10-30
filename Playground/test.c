/* This program would sort the input strings in
 * an ascending order and would display the same
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void display(char **output);
// void display(char *output)
// {
//    printf("%s\n", output);
// }
// void display(char **output)
// {
//    printf("%s\n", *output);
//    *output="asdasd";

// }

int main()
{
   int i, n;
   printf("Enter the number of integers: ");
   scanf("%d", &n);
   int *ptr = (int *)malloc(n * sizeof(int));

   for (i = 0; i < n; i++)
   {
      printf("Enter an integer:");
      scanf("%d", ptr + i);
   }

   for (i = 0; i < n; i++)
   {
      printf("%d ", *(ptr + i));
   }

   return 0;
}
