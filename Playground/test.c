#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void print_unlock_patterns_r(int pad[3][3], int x, int y, int step)
{
  printf("*******==============\n\n");
  //right, down,left,top
  static int const directions[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  pad[y][x] = 1 + step;

  for (int i = 0; i < 4; i++)
  {
    int xp = x + directions[i][0];
    int yp = y + directions[i][1];

    //  printf("%d %d \n", xp,yp);

    if (xp >= 0 && xp < 3 && yp >= 0 && yp < 3 && pad[yp][xp] == 0)
    {
      // printf("row = %d, col = %d , i = %d , value = %d\n", yp, xp, i, pad[yp][xp]);
      print_unlock_patterns_r(pad, xp, yp, pad[y][x]);
      // printf("END OF IF, current i = %d\n",i);
    }
    // else
    // {
    //   printf("--------- else =====> col = %d, row = %d , i = %d , value = %d\n", xp, yp, i, pad[yp][xp]);
    // }
    // for (int i = 0; i < 3; i++)
    // {
    //   for (int j = 0; j < 3; j++)
    //   {
    //     printf("%d", pad[i][j]);
    //   };
    //   puts("");
    // }
    puts("////");
  }

  if (step == 8)
  {
    for (int i = 0; i < 3; i++, puts(""))
    {
      for (int j = 0; j < 3; j++)
      {
        printf("%d", pad[i][j]);
      };
    }

    puts("");
  }
  printf("setting pad[y][x] to 0\n");
  //pad[y][x] = 0;

  // printf("XXXXXXXXXXXXXXXXXXXXXXXX\n");
  // for (int i = 0; i < 3; i++, puts(""))
  // {
  //   for (int j = 0; j < 3; j++)
  //   {
  //     printf("%d", pad[i][j]);
  //   };
  //   //}

  //   //puts("");
  // }
  printf("XXXXXXXXXXXXXXXXXXXXXXXX\n");
}

void print_unlock_patterns()
{
  int pad[3][3];
  memset(pad, 0, sizeof(pad));
  print_unlock_patterns_r(pad, 0, 0, 0);
}

int main(void)
{
  print_unlock_patterns();
  return 0;
}