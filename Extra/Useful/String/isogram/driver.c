
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
FILE *h_open(char *filename);
void read_file(FILE *file_pointer, char arr[100]);

int isogram(char *s)
{
    char buffer[100]; //changed from MAX+1 to MAX
    //char arr[100];
    char *filename = "isogram.txt";
    FILE *file_pointer = h_open(filename);
    int line = 0;
    // int temp_mx = 0;
    // int temp_my = 0;
    // char *t[256];
    // while (fscanf(file_pointer, "%s", buffer) != EOF)
    // {
    //     t[line] = malloc(strlen(buffer) + 1);
    //     strcpy(t[line], buffer);
    //     line++;
    //     if (line == 100)
    //         break;
    // }
    // // printf("line = %d\n", line);
    // for (int i = 0; i < line; i++)
    // {
    //     printf("%s\n", t[i]);
    // }
    // char flag[256] = {{0}};
    char str[256];

    strcpy(str, s);
    int len = strlen(str);
    int arr[256] = {0};
    for (int i = 0; i < len; i++)
    {
        arr[str[i]] += 1;
    }
    for (int i = 0; i < 256; i++)
    {
        if (arr[i] > 1)
        {
            return false;
        }
    }

    int index = 0;
    // while (t[index])
    // {
    //     free(t[index++]);
    // }
    // free(t);
    printf("end of function\n");

    return true;
}

FILE *h_open(char *filename)
{
    FILE *file_pointer = fopen(filename, "r");
    if (!file_pointer)
    {
        perror("Couldddnd't open file\n");
    }
    return file_pointer;
}
void read_file(FILE *file_pointer, char arr[100])
{
}