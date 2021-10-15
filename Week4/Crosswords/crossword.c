#include "crossword.h"
#define MAX 100
void fillBoard(crossword *cw, char *ip);
void check_possible_across(crossword *cw, char cross[MAX][MAX], int y, int x, int *k);
void check_possible_down(crossword *cw, char down[MAX][MAX], int y, int x, int *k);

// Might be useful to be able to print them
// to hep with debugging
void print_crossword(const crossword *c)
{
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         printf("%c", c->arr[y][x]);
      }
      printf("\n");
   }
}

bool str2crossword(int sz, char *ip, crossword *cw)
{
   printf("********* str2crossword start : ******** \n\n");

   if (ip == NULL)
   {
      printf("ip == NULL, returning false. \n");
      return false;
   }

   int ip_length = (int)strlen(ip);
   // printf("currently ip is %s\n", ip);
   // printf("sz = %d\n", sz);
   // printf("size of ip = %d\n", ip_length);
   if (sz <= 0 || ip_length == 0 || ip_length % sz != 0)
   {
      printf("false...\n");
      return false;
   }
   cw->sz = sz;
   fillBoard(cw, ip);

   return true;
}

void fillBoard(crossword *cw, char *ip)
{

   printf("GRID is %d\n", cw->sz);
   int k = 0;
   for (int r = 0; r < cw->sz; r++)
   {
      for (int c = 0; c < cw->sz; c++)
      {
         cw->arr[r][c] = ip[k];
         k++;
      }
   }
}

// int getchecked(crossword c)
// {
// }

void getcluestring(const crossword *c, char *ans)
{
   char across[MAX];
   char down[MAX];
   int k = 1;

   //number the board;
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {

         check_possible_across(c, across, y, x, &k);
         check_possible_down(c, down, y, x, &k);
      }
      printf("\n");
   }
   print_crossword(c);
}

void check_possible_across(crossword *c, char cross[MAX][MAX], int y, int x, int *k)
{
   printf("in across num of k = %d\n", *k);
   if (
       (c->arr[y][x] == '.') &&
       (x == 0 || c->arr[y][x - 1] == 'X') &&
       (c->arr[y][x + 1] == '.'))
   {
      c->arr[y][x] = *k + '0';
      *k = *k + 1;
   }

   // if(cw->arr[y][x]=='.'){
   //    printf("shi");
   //    printf(cw->arr[y][x]);
   // }
}
void check_possible_down(crossword *c, char down[MAX][MAX], int y, int x, int *k)
{
   printf("in DOWN num of k = %d\n", *k);
   if (

       (c->arr[y][x] == '.') &&
       (y == 0 || c->arr[y - 1][x] == 'X') &&
       (c->arr[y + 1][x] == '.') &&
       (c->arr[y + 2][x] == '.'))
   {
      c->arr[y][x] = *k + '0';
      *k = *k + 1;
   }
}

void test(void)
{
   printf("test function() \n");
}
