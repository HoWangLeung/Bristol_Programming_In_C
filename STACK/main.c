#include <stdio.h>
#include <stdlib.h>

void pad(int *s, int *d, int dim);
void depad(int *s, int *d, int dim);
void prnt(int **s, int dim);
void **n2dcalloc(int h, int w, size_t szelem);

int main(void)
{
    //int v[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; //example matrix
    int **a = (int **)n2dcalloc(3, 3, sizeof(int *));
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            a[y][x] = 1;
        }
        // printf("\n");
    }

    int dim = 3; //get dimension from program
    int *t;
    t = (int *)calloc((dim + 2) * (dim + 2), sizeof(int));

    for (int y = 1; y < dim; y++)
    {
        for (int x = 1; x < dim; x++)
        {
            /* code */
        }
        
    }
    

    //--------------------------------------------
    printf("Initial matrix:\n");
    prnt(a, dim);

    // pad(*a, t, dim);
    // prnt(*a, dim + 2);

    // //--------------------------------------------
    // printf("Depadded matrix:\n");
    // depad(t, dpad, dim + 2);
    // prnt(dpad, dim);

    // //free mem and return
    // free(t);
    // free(dpad);
    return 0;
}

void pad(int *s, int *d, int dim)
{
    int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            *(d + (i * (dim + 2) + (dim + 3 + j))) = *(s + i * dim + j);
}

void depad(int *s, int *d, int dim)
{
    int i, j;
    dim = dim - 2;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            *(d + i * dim + j) = *(s + (i * (dim + 2) + (dim + 3 + j)));
}

void prnt(int **s, int dim)
{
    int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
            printf("%d ", s[i][j]);
        printf("\n");
    }
}

void **n2dcalloc(int h, int w, size_t szelem)
{

    int i;
    void **p;
    p = calloc(h, sizeof(void *));
    if (p == NULL)
    {
        printf("Cannot calloc() space");
    }
    for (i = 0; i < h; i++)
    {
        p[i] = calloc(w, szelem);
        if (p[i] == NULL)
        {
            printf("Cannot calloc() space");
        }
    }
    return p;
}
