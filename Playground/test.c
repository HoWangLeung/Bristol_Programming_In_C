#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define R 12
#define C 12
#define MAX_LEN 100
void simulate(int a[R][C]);
void get_player_board(int board[R][C], char *fileName);

int main()
{

    int p1[R][C];
    memset(p1, 0, sizeof(p1));

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            printf("%c", p1[r][c]);
        }
        printf("\n");
    }

    return 0;
}
