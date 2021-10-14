#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct RandStart
{
    int x;
    int y;
} RandStart;

#define R 12
#define C 12
#define TR 7
#define TC 2
#define MAX_LEN 100
void simulate(int a[R][C]);
void get_player_board(int board[R][C], char *target_file);
void fillArrWithZero(int board[R][C]);
void printBoard(int board[R][C]);
void getFileData(int tmp[TR][TC], char *target_file);
void fillBoard(int board[R][C], int tmp[TR][TC], RandStart randStart);

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc != 3)
    {
        printf("INCORRECT USAGE \n");
        exit(1);
    }
    char *file1 = argv[1];
    char *file2 = argv[2];
    int p1[R][C] = {0};
    //memset(p1, 0, sizeof(p1));
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            printf("%c", p1[r][c]);
        }
    }
    get_player_board(p1, file1);
    //get_player_board(p2, file2);

    return 0;
}

void get_player_board(int board[R][C], char *target_file)
{
    RandStart randStart;
    int tmp[TR][TC];
    fillArrWithZero(board);
    getFileData(tmp, target_file);
    //create a random starting point;
    randStart.x = rand() % ((R + 1) - 0) + 0;
    randStart.y = rand() % ((C + 1) - 0) + 0;
    fillBoard(board, tmp, randStart);
}

void fillBoard(int board[R][C], int tmp[TR][TC], RandStart randStart)
{

    // printf("%d %d\n",randStart.x,randStart.y);

    for (int i = 0; i < TR; i++)
    {

        board[i][0] = tmp[i][0];
        board[i][1] = tmp[i][1];
    }
    printBoard(board);
}

void getFileData(int tmp[TR][TC], char *target_file)
{
    printf("f= %s\n", target_file);
    FILE *fp;
    fp = fopen(target_file, "r");
    if (fp == NULL)
    {
        perror("Failed: ");
        exit(1);
    }
    char buffer[MAX_LEN];
    int init[7][2];
    int i = 0;
    while (fgets(buffer, MAX_LEN - 1, fp))
    {

        if (buffer[0] == '#')
        {
            continue;
        };
        //printf("%c\n", buffer[0]);
        init[i][0] = buffer[0] - '0';
        init[i][1] = buffer[2] - '0';
        i++;
    }
    memcpy(tmp, init, sizeof(int) * TR * TC);
    fclose(fp);
}

void fillArrWithZero(int board[R][C])
{
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            board[r][c] = 0;
        }
    }
    printf("finished\n");
}
void printBoard(int board[R][C])
{
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            printf("%d", board[r][c]);
        }
        printf("\n");
    }
}

void simulate(int a[R][C])
{
    int b[R][C];
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            b[r][c] = a[r][c];
        }
    }

    int num_1_neighbour = 0;
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            num_1_neighbour = 0;
            if ((r - 1 >= 0) && (c - 1 >= 0) && (r + 1 < R) && (c + 1 < C))
            {

                if (a[r - 1][c - 1] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r - 1][c] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r - 1][c + 1] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r][c - 1] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r][c + 1] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r + 1][c - 1] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r + 1][c] == 1)
                {
                    num_1_neighbour++;
                }
                if (a[r + 1][c + 1] == 1)
                {
                    num_1_neighbour++;
                }

                if (a[r][c] == 1 && (num_1_neighbour == 2 || num_1_neighbour == 3))
                {
                    b[r][c] = 1;
                }
                else if (a[r][c] == 0 && num_1_neighbour == 3)
                {
                    b[r][c] = 1;
                }
                else
                {
                    b[r][c] = 0;
                }
            }
            printf("%d", b[r][c]);
        }

        printf("\n");
    }

    printf("\n");
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            a[r][c] = b[r][c];
        }
    }
}
