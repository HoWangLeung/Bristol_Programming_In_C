
#include "crossword.h"
#include <ctype.h>
#define MAX 1000



void fillBoard(crossword *cw, char *ip);
void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *can_go_right);
void check_down(const crossword *c, int y, int x, char down[MAX], int *count, bool *can_go_right);
bool left_has_across(crossword c, int y, int x);
bool top_has_down(crossword c, int y, int x);

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
   if (ip == NULL)
   {
      return false;
   }
   int ip_length = (int)strlen(ip);
   if (sz <= 0 || ip_length == 0 || ip_length % sz != 0)
   {
      return false;
   }
   cw->sz = sz;
   fillBoard(cw, ip);
   return true;
}

void fillBoard(crossword *cw, char *ip)
{
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

bool left_has_across(crossword c, int y, int x)
{

   printf("%d %d left has across check  ========================\n", y, x);

   while (x >= 0)
   {
      if (
          (c.arr[y][x - 1] == 'X' || x == 0) &&
          (c.arr[y][x + 1] == '.') &&
          (c.arr[y][x] == '.'))
      {
         printf("%d %d has at least one across\n\n", y, x);
         //c.arr[y][x] = '1';
         return 1;
      }
      x--;
      if (c.arr[y][x] == 'X')
      {
         return 0;
      }
   }
   printf("%d %d DOES NOT HAVE across\n\n", y, x);
   // print_crossword(&c);

   return 0;
}

bool top_has_down(crossword c, int y, int x)
{
   printf("%d %d top has down check  ========================\n", y, x);
   while (y >= 0)
   {
      printf("%d %d hello world\n", y, x);
      if (
          (c.arr[y - 1][x] == 'X' || y == 0) &&
          (c.arr[y][x] == '.') &&
          (c.arr[y + 1][x] == '.'))
      {
         printf("%d %d has at least one down <<<< \n\n", y, x);
         // c.arr[y][x] = '1';
         return 1;
      }
      y--;
      if (c.arr[y][x] == 'X')
      {
         return 0;
      }
   }
   printf("%d %d DOES NOT HAVE down <<<< \n\n", y, x);

   return 0;
}

int getchecked(crossword c)
{
   bool has_left = 0;
   bool has_top = 0;
   int sum = 0;
   int num_of_blank = 0;

   //  printf("get checked ========================\n");
   for (int y = 0; y < c.sz; y++)
   {
      for (int x = 0; x < c.sz; x++)
      {

         if (c.arr[y][x] == '.')
         {
            num_of_blank += 1;
            has_left = left_has_across(c, y, x);
            has_top = top_has_down(c, y, x);
            if (has_left == 1 && has_top == 1)
            {
               printf("*********** %d %d matches both ***********\n", y, x);
               sum += 1;
            }
         }
      }
   }

   printf("number of sum = %d\n", sum);
   printf("number of X = %d\n", num_of_blank);
   int ans = round((double)sum * 100 / num_of_blank);
   printf("ans = %2d\n", ans);

   return ans;
}

void getcluestring(const crossword *c, char *ans)
{
   char across[MAX] = "";
   char down[MAX] = "";
   across[0] = 'A';
   down[0] = 'D';
   int count = 0;
   bool can_go_right = false;
   print_crossword(c);
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         check_across(c, y, x, across, &count, &can_go_right);
         check_down(c, y, x, down, &count, &can_go_right);
      }
   }
   ans[0] = '\0';
   strcat(ans, across);
   strcat(ans, "|");
   strcat(ans, down);

   printf("=====result====\n");
   // printf("%s\n\n", across);
   // printf("%s\n\n", down);
   printf("%s\n\n", ans);
}

void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *can_go_right)
{
   printf("====> Across %d %d\n", y, x);
   if (
       (c->arr[y][x - 1] == 'X' || x == 0) &&
       (c->arr[y][x + 1] == '.') &&
       (c->arr[y][x] == '.'))
   {
      *count += 1;
      sprintf(&across[strlen(across)], "-%d", *count);
      *can_go_right = true;
      printf("add to across\n");
   }
   printf("%s\n\n", across);
}
void check_down(const crossword *c, int y, int x, char down[MAX], int *count, bool *can_go_right)
{
   printf("Down %d %d\n", y, x);
   if (
       (c->arr[y - 1][x] == 'X' || y == 0) &&
       (c->arr[y][x] == '.') &&
       (c->arr[y + 1][x] == '.'))
   {
      if (*can_go_right == 0)
      {
         *count += 1;
      }
      sprintf(&down[strlen(down)], "-%d", *count);
      printf("add to down\n");
   }
   *can_go_right = 0;
   printf("%s\n\n", down);
}

void test(void)
{
   printf("test function() \n");
}
