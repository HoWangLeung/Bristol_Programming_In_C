#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define FNAME "Maze.txt"
#define BIGSTR 500
void printBoard(const char board[100][100], int sz);
void dfs(char board[100][100], int y, int x);
int main()
{
    FILE *fp = fopen(FNAME, "r");
    char board[100][100];
    int line = 0;
    char input[512];
    char sizeArr[512];
    int sz;
    while (fgets(input, sizeof(input), fp))
    {
        if (line == 0)
        {
            char *token = strtok(input, " ");
            sz = atoi(token);
        }
        else
        {
            for (int i = 0; i < strlen(input); i++)
            {
                board[line - 1][i] = input[i];
            }
        }
        line++;
    }
    dfs(board, 1, 0);
    printf("finished\n");

    return 0;
}

void dfs(char board[100][100], int y, int x)
{
    static int direction[4][2] = { {1, 0}, {0, 1}, {-1, 0},{0, -1},};
    printf("%d %d \n", y, x);
    if (x < 0 || x > 10 || y < 0 || y > 10)
    {
        if (x == 10)
        {
            printf("******************* => %d,%d\n", y, x);
        }
        return;
    }

    if (board[y][x] != ' ')
    {
        //printf("return 2 ");
        return;
    }

    board[y][x] = '.';
    printBoard(board, 10);

    if (board[y - 1][x] == '#' && board[y + 1][x] == '#' && x==9)
    {
        printf("found th exit with coordinate %d,%d\n",x,y);
        exit(0);
    }

    for (int i = 0; i < 4; i++)
    {
        int nx = x + direction[i][0];
        int ny = y + direction[i][1];
        dfs(board, ny, nx);
    }

    board[y][x] = ' ';
}

void printBoard(const char board[100][100], int sz)
{
    for (int y = 0; y < sz; y++)
    {
        for (int x = 0; x < sz; x++)
        {
            printf("%c", board[y][x]);
        }
        printf("\n");
    }
}