#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define R 150
#define C 80
#define MAX_LEN 100
void simulate(int a[R][C]);

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("INCORRECT USAGE \n");
        exit(1);
    }
    char *target_file = argv[1];
    int target_iteration = atoi(argv[2]);

    FILE *fp;

    fp = fopen(target_file, "r");
    if (fp == NULL)
    {
        perror("Failed: ");
        return 1;
    }
    char buffer[MAX_LEN];
    int init[R][C];
    int t1[6];
    int t2[6];
    int i = 0;
    //Assing to Temp array
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        printf("c = %c\n", buffer[0]);
        if (buffer[0] == '#')
        {
            continue;
        };
        t1[i] = buffer[0] - '0';
        t2[i] = buffer[2] - '0';
        i++;
    }

    //printf("actual %lu\n",sizeof(t1) / sizeof(t1[0]));
    fclose(fp);
    // memmove(&t1[0], &t1[0 + 1], 6 - 0);
    // memmove(&t2[0], &t2[0 + 1], 6 - 0);

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            init[r][c] = 0;
            // printf("%d", init[r][c]);
        }
        // printf("\n");
    }

    for (int i = 0; i < 6; i++)
    {
        init[R / 2 + t1[i]][C / 2 + t2[i]] = 1;
    }
    //print result
    // for (int r = 0; r < R; r++)
    // {
    //     for (int c = 0; c < C; c++)
    //     {
    //         printf("%d", init[r][c]);
    //     }
    //     printf("\n");
    // }

    int a[R][C];
    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            a[r][c] = init[r][c];
            printf("%d", init[r][c]);
        }
        printf("\n");
    }
    printf("====NEW START======\n");

    for (int i = 0; i < target_iteration; i++)
    {
        simulate(a);
    }
    return 0;
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
