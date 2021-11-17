#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40
#define MAX 36
char **get_arr(char board[6][6]);
void free_list(char **arr);

int main()
{
    char board[6][6];
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            board[y][x] = '1';
        }
    }

    char **arr = get_arr(board);

    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            printf("%c", arr[y][x]);
        }
        printf("\n");
    }

    free_list(arr);

    return 0;
}

char **get_arr(char board[6][6])
{

    char **temp_arr = (char **)calloc(sizeof(char *), (MAX));
    for (int i = 0; i < 6; i++)
    {
        temp_arr[i] = (char *)calloc(sizeof(char), 6 + 1);
        memcpy(temp_arr[i], board[i], 6);
    }
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            temp_arr[y][x] = '0';
        }
    }

    return temp_arr;
}

void free_list(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}
