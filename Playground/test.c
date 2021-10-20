#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{

  char *s = "42";
  printf("%c\n", s);
  while (*s)
  {
    printf("%c\n", *s);
    *s++;
  }


}