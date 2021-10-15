#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BIGSTR 1000
#define GRID 100

struct crossword
{
    char arr[GRID][GRID];
    int sz;
};
typedef struct crossword crossword;

void fillBoard(crossword *cw, char *ip);
void print_crossword(const crossword *c);
int main()
{

    crossword c;

    c.sz = 3;
    fillBoard(&c, "...XX....");
    print_crossword(&c);
    return 0;
}

void fillBoard(crossword *cw, char *ip)
{

    printf("GRID is %d\n", cw->sz);
    int k = 0;
    for (int r = 0; r < cw->sz; r++)
    {
        for (int c = 0; c < cw->sz; c++)
        {
            cw->arr[r][c] = ip[k];
            k++;
            if (k == cw->sz)
                break;
        }
    }
}

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
