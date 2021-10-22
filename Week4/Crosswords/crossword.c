
#include "crossword.h"
#include <ctype.h>
#include <string.h>
#define MAX 1000
#define BIGSTR 1000
#define HUNDRED 100
// valid_across: if a square is a valid_across it means (1)square on the left is black, (2) this square itself is blank,(3) square on the right is blank.
// valid_down:similar concept as above but for down

//fill the 2d array with value from char *ip
void fillBoard(crossword *cw, char *ip);
//Check if a given position is valid across, used together with check_down() to keep track of the count
void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *valid_across);
//Check if a given position is valid down, used together with check_down() to keep track of the count
void check_down(const crossword *c, int y, int x, char down[MAX], int *count, bool *valid_across);
//Given a position, keep checking squares on the left until hitting the boundary, return true if one of the squares on the left or itself is a valid across.
bool left_has_across(const crossword *c, int y, int x);
//Given a position, keep checking squares above, return true if one of the squares below or itself is a valid_down
bool top_has_down(const crossword *c, int y, int x);
//Given a position, determine if the square is blank
bool cur_is_blank(const crossword *c, int y, int x);
//Given a position, determine if the square on the left is blank
bool left_is_solid(const crossword *c, int y, int x);
//Given a position, determine if the square on the right is blank
bool right_is_blank(const crossword *c, int y, int x);
//Given a position, determine if the square on the top is solid
bool top_is_solid(const crossword *c, int y, int x);
//Given a position, determine if the square below is blank
bool down_is_blank(const crossword *c, int y, int x);
//Given a position, determine if the square is solid
bool cur_is_solid(const crossword *c, int y, int x);
//return true if top_is_solid() && cur_is_blank() && down_is_blank() are all true;
bool is_valid_down(const crossword *c, int y, int x);
//return true if left_is_solid() && cur_is_blank() && right_is_blank() are all true;
bool is_valid_across(const crossword *c, int y, int x);
//In a valid crossword game,there should be a minimum 1 across and 1 down to be playable.
bool minimum_requirement(const crossword *c);
//used to test if the fill_board() function works properly
bool validate_filled_board(const crossword *c, char *ip);
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
   if (sz <= 0 || ip_length == 0 || ip_length != sz * sz)
   {
      return false;
   }

   if ((strchr(ip, 'X') && strchr(ip, '*')) ||
       (strchr(ip, '.') && strchr(ip, ' ')))
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
bool left_has_across(const crossword *c, int y, int x)
{
   while (x >= 0)
   {
      if (is_valid_across(c, y, x))
      {
         return true;
      }
      x--;
      if (cur_is_solid(c, y, x))
      {
         return false;
      }
   }
   return false;
}
bool top_has_down(const crossword *c, int y, int x)
{
   while (y >= 0)
   {
      if (is_valid_down(c, y, x))
      {
         return true;
      }
      y--;
      if (cur_is_solid(c, y, x))
      {
         return false;
      }
   }
   return false;
}
int getchecked(crossword c)
{
   int sum = 0;
   int num_of_blank = 0;
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
   int ans = round((double)sum * HUNDRED / num_of_blank);
 
   return ans;
}
void getcluestring(const crossword *c, char *ans)
{
   char across[MAX] = "";
   char down[MAX] = "";
   strcpy(across, "A");
   strcpy(down, "D");
   int count = 0;
   bool valid_across = false;
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         check_across(c, y, x, across, &count, &valid_across);
         check_down(c, y, x, down, &count, &valid_across);
      }
   }
   sprintf(ans, "%s|%s", across, down);
}

void check_across(const crossword *c, int y, int x, char across[MAX], int *count, bool *valid_across)
{
   if (is_valid_across(c, y, x))
   {
      *count += 1;
      sprintf(&across[strlen(across)], "-%d", *count);
      *valid_across = true;
   }
}
void check_down(const crossword *c, int y, int x, char down[MAX], int *count, bool *valid_across)
{
   if (is_valid_down(c, y, x))
   {
      //If the same square is not a valid across, then the count is incremented
      if (*valid_across == false)
      {
         *count += 1;
      }
      sprintf(&down[strlen(down)], "-%d", *count);
   }
   *valid_across = false;
}

void test(void)
{
   char str[BIGSTR];
   //=============================================
   // #Test if fillBoard() fills the board correctly
   crossword c;

   char *ip = ".........";
   int sz = 3;
   c.sz = sz;
   fillBoard(&c, ip);
   assert(validate_filled_board(&c, ip) == true);

   ip = "X........";
   sz = 3;
   c.sz = sz;
   fillBoard(&c, ip);
   assert(validate_filled_board(&c, ip) == true);

   ip = "XXX...X.X";
   sz = 3;
   c.sz = sz;
   fillBoard(&c, ip);
   assert(validate_filled_board(&c, ip) == true);
   //=============================================

   //=============================================
   // #Test corner cases that were not covered

   //Not valid if there is no blank square
   assert(!str2crossword(5, "XXXXXXXXXXXXXXXXXXXXXXXXX", &c));
   assert(!str2crossword(5, "*************************", &c));
   //have across or down
   assert(str2crossword(5, "X..XXXXXXXXXXXXXXXXXXXXXX", &c));
   assert(str2crossword(5, "X..XXX.XXXXXXXXXXXXXXXXXX", &c));
   assert(str2crossword(5, "X..XXXX.XXXXXXXXXXXXXXXXX", &c));
   assert(!str2crossword(5, "X..XXXX.XXXXXXXXXXXXXXXXXX..XXXX.XXXXXXXXXXXXXXXXXX..XXXX.XXXXXXXXXXXXXXXXX", &c));

   //Invalid characters
   assert(!str2crossword(5, "&####^.^^^^^^^^^^())-^&!@X", &c));
   assert(!str2crossword(5, "X..X#X.XXXXXXXXXX())-^&!@X", &c));
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));

   //'X' and '*' are both valid,but using both at the same time is confusing
   assert(!str2crossword(5, "....*.**.X.X......X.XX...", &c));
   assert(!str2crossword(5, "    *.**.X.X......X.XX...", &c));

   //same for ' ' and '.'
   assert(!str2crossword(5, ".... .  . . ...... .  ...", &c));
   assert(!str2crossword(5, "X* ...  . . ...... .  ...", &c));

   //=============================================

   //=============================================
   // #Testing my own functions
   //setup the board using example from handout
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
   assert(cur_is_blank(&c, 0, 0));
   assert(cur_is_blank(&c, 0, 3));

   //0,4 is 'X', should return false
   assert(!cur_is_blank(&c, 0, 4));
   assert(!cur_is_blank(&c, 1, 1));

   //right of 0,0 is blank, should return true
   assert(right_is_blank(&c, 0, 0));
   assert(right_is_blank(&c, 0, 2));
   assert(right_is_blank(&c, 2, 3));
   // right of 0,3 is 'X' should return false
   assert(!right_is_blank(&c, 0, 3));
   assert(!right_is_blank(&c, 1, 0));
   assert(!right_is_blank(&c, 1, 3));
   assert(!right_is_blank(&c, 2, 0));

   assert(top_is_solid(&c, 1, 4));
   assert(top_is_solid(&c, 2, 1));
   assert(top_is_solid(&c, 4, 3));
   assert(top_is_solid(&c, 3, 1));

   assert(!top_is_solid(&c, 1, 0));
   assert(!top_is_solid(&c, 1, 1));

   //area outside the boundary is counted as solid
   assert(top_is_solid(&c, 0, 0));
   assert(down_is_blank(&c, 0, 0));
   assert(!down_is_blank(&c, 0, 1));
   assert(cur_is_solid(&c, 0, 4));
   assert(!cur_is_solid(&c, 0, 0));

   //is_valid_down = true if
   //(1)square above is solid
   //(2)current square is blank and
   //(3)square below is solid
   assert(is_valid_down(&c, 0, 0));
   assert(!is_valid_down(&c, 1, 0));
   assert(!is_valid_down(&c, 0, 1));
   assert(!is_valid_down(&c, 0, 2));
   assert(is_valid_across(&c, 2, 2));
   assert(is_valid_across(&c, 4, 2));
   assert(!is_valid_across(&c, 0, 1));
   assert(!is_valid_across(&c, 2, 4));

   //has 1 across and 1 down
   fillBoard(&c, "X..XXX.XXXXXXXXXXXXXXXXXX");
   assert(minimum_requirement(&c));

   //This board only has 1 across, should not be a valid game
   fillBoard(&c, "X.XXXXXXXXXXXXXXXXXXXXXXX");
   assert(!minimum_requirement(&c));

   //setup the board
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));

   //Testing if check_across() works as expected
   char across[MAX] = "";
   char down[MAX] = "";
   strcpy(across, "A");
   strcpy(down, "D");
   int count = 0;
   bool valid_across = false;
   check_across(&c, 0, 0, across, &count, &valid_across);
   assert(valid_across == true);
   assert(count = 1);
   //reset array for testing
   memset(across, 0, sizeof(across));
   memset(down, 0, sizeof(down));

   strcpy(across, "A");
   strcpy(down, "D");
   count = 0;
   valid_across = false;
   //position 0,1 is not a valid across, thus 'valid_across'=false and count remains unchanged.
   check_down(&c, 0, 1, across, &count, &valid_across);
   assert(valid_across == false);
   assert(count == 0);
   //=============================================

   //=============================================
   //Test top_has_down() and left_has_across()
   assert(str2crossword(5, "....X.XX.X.X......X.XX...", &c));
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str) == 0);
   int num_of_blank = 0;
   int sum = 0;

   assert(top_has_down(&c, 0, 3));
   assert(top_has_down(&c, 1, 3));
   assert(top_has_down(&c, 2, 3));
   assert(top_has_down(&c, 3, 4));
   assert(top_has_down(&c, 2, 4));
   assert(top_has_down(&c, 4, 4));
   assert(top_has_down(&c, 0, 0));
   assert(!top_has_down(&c, 3, 1));
   assert(!top_has_down(&c, 4, 3));

   assert(left_has_across(&c, 0, 0));
   assert(left_has_across(&c, 0, 1));
   assert(left_has_across(&c, 0, 2));
   assert(left_has_across(&c, 4, 2));
   assert(!left_has_across(&c, 2, 0));
   assert(!left_has_across(&c, 1, 3));
   assert(!left_has_across(&c, 3, 4));

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
   assert(num_of_blank == 17);
   assert(sum == 9);

   //=============================================

   //=============================================
   // #Repeat the same tests with '*' and ' '

   assert(str2crossword(3, "         ", &c));
   assert(c.sz == 3);
   getcluestring(&c, str);
   assert(strcmp("A-1-4-5|D-1-2-3", str) == 0);
   assert(getchecked(c) == 100);

   assert(str2crossword(5, "    * ** * *      * **   ", &c));
   assert(c.sz == 5);
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str) == 0);
   assert(strcmp("A-1-3-5-6|D-1-2-3-4", str) == 0);
   num_of_blank = 0;
   sum = 0;
   assert(top_has_down(&c, 0, 0));
   assert(left_has_across(&c, 0, 0));
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
   assert(num_of_blank == 17);
   assert(sum == 9);
   assert(getchecked(c) == 53);

   assert(str2crossword(5, "*   *               *   *", &c));
   assert(c.sz == 5);
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7-8|D-1-2-3-4-5", str) == 0);
   assert(getchecked(c) == 100);

   assert(str2crossword(7, "  *    * ** * * ** *      *  ** **         ** ** ", &c));
   assert(c.sz == 7);
   getcluestring(&c, str);
   assert(strcmp("A-1-3-6-8|D-2-4-5-6-7", str) == 0);
   assert(getchecked(c) == 32);

   assert(str2crossword(7, "* *        * ** * * *       * * * *    * ** *    ", &c));
   assert(c.sz == 7);
   getcluestring(&c, str);
   assert(strcmp("A-2-4-5-6-7|D-1-2-3", str) == 0);
   assert(getchecked(c) == 33);

   assert(str2crossword(7, "   *    *   *    *   * *** *   *    *   *    *   ", &c));
   assert(c.sz == 7);
   getcluestring(&c, str);
   assert(strcmp("A-1-3-5-6-8-10-12-14-15-16|D-1-2-3-4-7-9-10-11-12-13", str) == 0);
   assert(getchecked(c) == 67);

   assert(str2crossword(7, "        * ***  *      * * *      *  *** *        ", &c));
   assert(c.sz == 7);
   getcluestring(&c, str);
   assert(strcmp("A-1-4-6-7|D-1-2-3-5", str) == 0);
   assert(getchecked(c) == 33);

   assert(str2crossword(8, "     * ** * *          ** * *      * * **          * * ** *     ", &c));
   assert(c.sz == 8);
   getcluestring(&c, str);
   assert(strcmp("A-1-5-6-7-8-11-12-13|D-2-3-4-5-9-10", str) == 0);
   assert(getchecked(c) == 43);

   //=============================================
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
bool validate_filled_board(const crossword *c, char *ip)
{
   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         if (c->arr[y][x] != *ip++)
         {
            return false;
         }
      }
   }
   return true;
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

//Most crossword would have at least 1 across or 1 down, the puzzle is hardly plyable if not
bool minimum_requirement(const crossword *c)
{
   int minium_across_or_down = 0;

   for (int y = 0; y < c->sz; y++)
   {
      for (int x = 0; x < c->sz; x++)
      {
         if (is_valid_across(c, y, x) || is_valid_down(c, y, x))
         {
            minium_across_or_down++;
         }
      }
   }
   if (minium_across_or_down < 1)
   {
      return false;
   }
   return true;
}
