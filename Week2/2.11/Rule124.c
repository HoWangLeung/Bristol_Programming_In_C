#include <stdio.h>
#include <stdbool.h>
#define WIDTH 30

void rule(int t[]);
int main(void)
{
    int count = 0, i;
    int t[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    while (count++ < 20)
    {
        for (i = 0; i < WIDTH; i++)
        {
            printf("%d", t[i]);
        }
        printf("\n");
        rule(t);
    }
    return 0;
}

void rule(int t[])
{
    int t1[WIDTH];
    int ix, lx, rx, i;

    for (ix = 0; ix < WIDTH; ix++)
    {
        lx = (ix + WIDTH - 1) % WIDTH; // left pixel wraps to other end
        rx = (ix + 1) % WIDTH;         // right pixel wraps to other end

        if ((t[lx] == 0) && (t[ix] == 0) && (t[rx] == 0))
        {
            t1[ix] = 0;
        }
        else if ((t[lx] == 0) && (t[ix] == 0) && (t[rx] == 1))
        {
            t1[ix] = 1;
        }
        else if ((t[lx] == 0) && (t[ix] == 1) && (t[rx] == 0))
        {
            t1[ix] = 1;
        }
        else if ((t[lx] == 0) && (t[ix] == 1) && (t[rx] == 1))
        {
            t1[ix] = 1;
        }
        else if ((t[lx] == 1) && (t[ix] == 0) && (t[rx] == 0))
        {
            t1[ix] = 0;
        }
        else if ((t[lx] == 1) && (t[ix] == 0) && (t[rx] == 1))
        {
            t1[ix] = 1;
        }
        else if ((t[lx] == 1) && (t[ix] == 1) && (t[rx] == 0))
        {
            t1[ix] = 1;
        }
        else
            t1[ix] = 0;
    }
    for (i = 0; i < WIDTH; i++)
    {
        t[i] = t1[i]; // error here was t[ix] = t1[ix]
    }
}