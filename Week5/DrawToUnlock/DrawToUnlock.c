#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct square
{
    int y;
    int x;
    bool checked;
    int next[4][2];
};
typedef struct square square;
void print_board(const int pad[3][3]);
void dfs(int pad[3][3], int y, int x, int step, int *count);
void dfs(int pad[3][3], int y, int x, int step, int *count)
{
    printf("%d %d \n", y, x);
    pad[y][x] = step + 1;
    int direction[][2] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}};

    for (int i = 0; i < 4; i++)
    {

        int nx = x+direction[i][0];
        int ny = y+direction[i][1];

        if (x >= 0 && x < 3 && pad[y][x] != 0)
        {
            dfs(pad, y, x + 1, step + 1, count);
        }
    }

    print_board(pad);
    printf("finished \n");
}

int main()
{
    int pad[3][3];
    square s;

    memset(pad, 0, sizeof(pad));
    int count = 0;
    print_board(pad);
    dfs(pad, 0, 0, 0, &count);

    return 0;
}

void print_board(const int pad[3][3])
{
    printf("\n");
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            printf("%d", pad[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
