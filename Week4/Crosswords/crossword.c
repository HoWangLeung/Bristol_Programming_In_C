
#include "crossword.h"
#include <ctype.h>
#define MAX 1000
#define BIGSTR 1000

void fillBoard(crossword *cw, char *ip);
void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *can_go_right);
void check_down(const crossword *c, int y, int x, char down[MAX], int *count, bool *can_go_right);
bool left_has_across(const crossword *c, int y, int x);
bool top_has_down(const crossword *c, int y, int x);
bool cur_is_blank(const crossword *c, int y, int x);
bool left_is_solid(const crossword *c, int y, int x);
bool right_is_blank(const crossword *c, int y, int x);
bool top_is_solid(const crossword *c, int y, int x);
bool down_is_blank(const crossword *c, int y, int x);
bool cur_is_solid(const crossword *c, int y, int x);
bool is_valid_down(const crossword *c, int y, int x);
bool is_valid_across(const crossword *c, int y, int x);
bool minimum_requirement(const crossword *c);
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
   if (!minimum_requirement(cw))
   {
      return false;
   }
   return true;
}

void fillBoard(crossword *cw, char *ip)
{
   int k = 0;
   for (int r = 0; r < cw->sz; r++)
   {
      for (int c = 0; c < cw->sz; c++)
      {
         cw->arr[r][c] = ip[k++];
      }
   }
}

bool left_has_across(const crossword *c, int y, int x)
{
   printf("%d %d leftsss has across check  ========================\n", y, x);
   while (x >= 0)
   {
      if (is_valid_across(c, y, x))
      {
         printf("%d %d has at least one across\n\n", y, x);
         return true;
      }
      x--;
      if (cur_is_solid(c, y, x))
      {
         return false;
      }
   }
   printf("%d %d DOES NOT HAVE across\n\n", y, x);
   // print_crossword(&c);
   return 0;
}

bool top_has_down(const crossword *c, int y, int x)
{
   printf("%d %d top has down check  ========================\n", y, x);
   while (y >= 0)
   {
      printf("%d %d hello world\n", y, x);
      if (is_valid_down(c, y, x))
      {
         printf("%d %d has at least one down <<<< \n\n", y, x);
         return true;
      }
      y--;
      if (cur_is_solid(c, y, x))
      {
         return false;
      }
   }
   printf("%d %d DOES NOT HAVE down <<<< \n\n", y, x);

   return false;
}

int getchecked(crossword c)
{
   int sum = 0;
   int num_of_blank = 0;

   //  printf("get checked ========================\n");
   for (int y = 0; y < c.sz; y++)
   {
      for (int x = 0; x < c.sz; x++)
      {
         if (cur_is_blank(&c, y, x))
         {
            num_of_blank += 1;
            if (left_has_across(&c, y, x) && top_has_down(&c, y, x))
            {
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
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         check_across(c, y, x, across, &count, &can_go_right);
         check_down(c, y, x, down, &count, &can_go_right);
      }
   }
   sprintf(ans, "%s|%s", across, down);
   printf("=====result====\n");
   // printf("%s\n\n", across);
   // printf("%s\n\n", down);
   printf("%s\n\n", ans);
}

void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *can_go_right)
{
   printf("====> Across %d %d\n", y, x);
   if (is_valid_across(c, y, x))
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
   if (is_valid_down(c, y, x))
   {
      if (*can_go_right == false)
      {
         *count += 1;
      }
      sprintf(&down[strlen(down)], "-%d", *count);
      printf("add to down\n");
   }
   *can_go_right = false;
   printf("%s\n\n", down);
}

void test(void)
{
   // char str[BIGSTR];
   crossword c;
   assert(!str2crossword(5, "XXXXXXXXXXXXXXXXXXXXXXXXX", &c));

   assert(!str2crossword(5, "X..XXXXXXXXXXXXXXXXXXXXXX", &c));

   assert(str2crossword(5, "X..XXX.XXXXXXXXXXXXXXXXXX", &c));

   assert(!str2crossword(5, "X..XXXX.XXXXXXXXXXXXXXXXX", &c));

   assert(!str2crossword(5, "X..XXX.XXXXXXXXXXXXXXXX@X", &c));
}

bool cur_is_blank(const crossword *c, int y, int x)
{
   return c->arr[y][x] == '.' || c->arr[y][x] == ' ';
}
bool left_is_solid(const crossword *c, int y, int x)
{
   return (c->arr[y][x - 1] == 'X' || c->arr[y][x - 1] == '*' || x == 0);
}
bool right_is_blank(const crossword *c, int y, int x)
{
   return c->arr[y][x + 1] == '.' || c->arr[y][x + 1] == ' ';
}

bool top_is_solid(const crossword *c, int y, int x)
{
   return (c->arr[y - 1][x] == 'X' || c->arr[y - 1][x] == '*' || y == 0);
}

bool down_is_blank(const crossword *c, int y, int x)
{
   return (c->arr[y + 1][x] == '.' || c->arr[y + 1][x] == ' ');
}

bool cur_is_solid(const crossword *c, int y, int x)
{
   return (c->arr[y][x] == 'X' || c->arr[y][x] == '*');
}

bool is_valid_down(const crossword *c, int y, int x)
{
   return top_is_solid(c, y, x) && cur_is_blank(c, y, x) && down_is_blank(c, y, x);
}

bool is_valid_across(const crossword *c, int y, int x)
{
   return left_is_solid(c, y, x) && cur_is_blank(c, y, x) && right_is_blank(c, y, x);
}

bool minimum_requirement(const crossword *c)
{
   int minium_across_or_down = 0;
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         if (is_valid_across(c, y, x) && is_valid_down(c, y, x))
         {
            minium_across_or_down++;
         }
      }
   }
   if (minium_across_or_down < 1)
   {
      printf("A valid crossword should have at least 1 pair of cross and down.\n");
      return false;
   }
   return true;
}
